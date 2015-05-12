package main

const (
	tcpPort  = 1000
	udpPort  = 2000
	httpPort = 8888
)

func main() {
	packetChan := make(chan *packet, 1024)
	errChan := make(chan error)

	go tcpHandler(tcpPort, packetChan, errChan)
	go udpHandler(udpPort, packetChan, errChan)

	httpHandler(httpPort, packetChan, errChan)
}
