// Implementation of a MultiEchoServer. Students should write their code in this file.

package p0

import (
	"bufio"
	"fmt"
	"net"
	"net/textproto"
)

const (
	CLIENT_MESSAGE_QUEUE_SIZE = 100
	SERVER_HOST               = "127.0.0.1"
)

type message []byte

type client struct {
	conn net.Conn

	exitChan      chan *client
	broadcastChan chan message
	notifyChan    chan message
	stopChan      chan interface{}
}

func makeClient(
	conn net.Conn,
	eChan chan *client,
	nChan chan message,
) *client {
	return &client{
		conn:          conn,
		exitChan:      eChan,
		broadcastChan: make(chan message, CLIENT_MESSAGE_QUEUE_SIZE),
		notifyChan:    nChan,
		stopChan:      make(chan interface{}),
	}
}

func (c client) Write(m message) {
	select {
	case c.broadcastChan <- m:
	default:
		return
	}
}

func (c *client) Serve() {
	go func() {
		reader := textproto.NewReader(bufio.NewReader(c.conn))
		for {
			m, err := reader.ReadLineBytes()
			if err != nil {
				c.stopChan <- err
				return
			}
			c.notifyChan <- append(m, '\n')
		}
	}()

	for {
		select {
		case <-c.stopChan:
			c.exitChan <- c
			c.conn.Close()
			return
		case m := <-c.broadcastChan:
			if _, err := c.conn.Write(m); err != nil {
				c.exitChan <- c
			}
		}
	}
}

func (c client) Close() {
	c.stopChan <- nil
}

type countRequest chan int

type multiEchoServer struct {
	clients []*client

	countRequestChan  chan countRequest
	newClientChan     chan *client
	clientExitChan    chan *client
	clientMessageChan chan message
	stopChan          chan interface{}
}

// New creates and returns (but does not start) a new MultiEchoServer.
func New() MultiEchoServer {
	return &multiEchoServer{
		clients: make([]*client, 0),

		countRequestChan:  make(chan countRequest),
		newClientChan:     make(chan *client),
		clientExitChan:    make(chan *client),
		clientMessageChan: make(chan message),
		stopChan:          make(chan interface{}),
	}
}

func (mes *multiEchoServer) Start(port int) error {
	ln, err := net.Listen("tcp", fmt.Sprintf("%s:%d", SERVER_HOST, port))
	if err != nil {
		return err
	}

	go func(ln net.Listener) {
		for {
			conn, err := ln.Accept()
			if err != nil {
				mes.stopChan <- err
				return
			}
			client := makeClient(
				conn,
				mes.clientExitChan,
				mes.clientMessageChan,
			)
			mes.newClientChan <- client
		}
	}(ln)

	go func(ln net.Listener) {
		// *the loop*
		for {
			select {
			case resp := <-mes.countRequestChan:
				resp <- len(mes.clients)
			case client := <-mes.newClientChan:
				mes.clients = append(mes.clients, client)
				go client.Serve()

			case client := <-mes.clientExitChan:
				for i, c := range mes.clients {
					if c == client {
						mes.clients = append(
							mes.clients[:i],
							mes.clients[i+1:]...,
						)
						break
					}
				}

			case message := <-mes.clientMessageChan:
				for _, c := range mes.clients {
					c.Write(message)
				}

			case <-mes.stopChan:
				ln.Close()
				return
			}
		}
	}(ln)

	return nil
}

func (mes *multiEchoServer) Close() {
	mes.stopChan <- nil
}

func (mes *multiEchoServer) Count() int {
	reqChan := make(chan int)
	mes.countRequestChan <- reqChan
	return <-reqChan
}
