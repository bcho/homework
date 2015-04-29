package main

import (
	"net"
)

func main() {
	l, err := net.ListenPacket("ip4:icmp", "0.0.0.0")
	if err != nil {
		panic(err)
	}
	defer l.Close()

	addr := &net.IPAddr{IP: net.IPv4(180, 97, 33, 107)}

	msg := MakeEchoMessage(1, 1, []byte("hello world"))

	l.WriteTo(msg.Marshal(), addr)
}
