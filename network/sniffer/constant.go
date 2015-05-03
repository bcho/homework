package main

const (
	LINE_DELIM = "--------------------------------------------------------------------------------"
)

const (
	LayerUnknown     = LayerType("unknown")
	LayerLink        = LayerType("link")
	LayerNetwork     = LayerType("network")
	LayerTransport   = LayerType("transport")
	LayerApplication = LayerType("application")

	EthernetIP4 = EthernetType(0x0800)

	// http://en.wikipedia.org/wiki/List_of_IP_protocol_numbers
	IPProtocolICMP = IPProtocol(0x01)
	IPProtocolTCP  = IPProtocol(0x06)
	IPProtocolUDP  = IPProtocol(0x11)
)

var (
	decoders []decodeFunc
)

func initDecoders() {
	decoders = []decodeFunc{
		decodeEthernet,
		decodeUnknown,
	}
}

func init() {
	initDecoders()
}
