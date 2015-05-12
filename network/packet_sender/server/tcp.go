package main

import (
	"fmt"
	"net"
)

func tcpHandler(port int, packetChan chan *packet, errChan chan error) {
	ln, err := net.Listen("tcp", fmt.Sprintf(":%d", port))
	if err != nil {
		errChan <- err
	}
	defer ln.Close()

	for {
		conn, err := ln.Accept()
		if err != nil {
			errChan <- err
		}
		defer conn.Close()

		packet, err := readPacket(packetTypeTCP, conn)
		if err != nil {
			errChan <- err
		}
		packetChan <- packet
	}
}
