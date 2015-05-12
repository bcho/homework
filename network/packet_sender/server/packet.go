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
	Type    packetType `json:"type"`
	Content string     `json:"content"`
	From    net.Addr   `json:"from"`
}

func readPacket(tp packetType, conn net.Conn) (*packet, error) {
	b := make([]byte, messageSize)
	n, err := conn.Read(b)
	if err != nil {
		return nil, err
	}
	b = b[:n]
	addr := conn.RemoteAddr() // always nil with udp?

	return &packet{tp, string(b), addr}, nil
}
