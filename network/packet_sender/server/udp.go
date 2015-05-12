package main

import (
	"net"
)

func udpHandler(port int, packetChan chan *packet, errChan chan error) {
	addr := net.UDPAddr{
		Port: port,
		IP:   net.ParseIP("127.0.0.1"),
	}
	conn, err := net.ListenUDP("udp", &addr)
	if err != nil {
		errChan <- err
	}
	defer conn.Close()

	for {
		packet, err := readPacket(packetTypeUDP, conn)
		if err != nil {
			errChan <- err
		}
		packetChan <- packet
	}
}
