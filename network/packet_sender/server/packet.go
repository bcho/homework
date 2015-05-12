package main

import (
	"net"
)

const (
	messageSize = 4096

	packetTypeTCP = "tcp"
	packetTypeUDP = "udp"
)

type packetType string

type packet struct {
	Type    packetType
	Content string
	From    net.Addr
}

func readPacket(tp packetType, conn net.Conn) (*packet, error) {
	// TODO use reader
	b := make([]byte, messageSize)
	n, err := conn.Read(b)
	if err != nil {
		return nil, err
	}
	b = b[:n]
	addr := conn.RemoteAddr() // always nil?

	return &packet{tp, string(b), addr}, nil
}
