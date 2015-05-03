// IP4 decoder.
package main

import (
	"encoding/binary"
	"fmt"
	"net"
	"strings"
)

type IPProtocol uint8

func (p IPProtocol) String() string {
	var name string
	switch p {
	case IPProtocolICMP:
		name = "ICMP"
	case IPProtocolTCP:
		name = "TCP"
	case IPProtocolUDP:
		name = "UDP"
	default:
		name = "UNKNOWN"
	}
	return fmt.Sprintf(
		"%s (0x%02x)",
		name,
		uint8(p), // have to convert into uint8 explicitly?
	)
}

func (p IPProtocol) Decoder() decodeFunc {
	switch p {
	case IPProtocolICMP:
		return decodeICMP
	case IPProtocolUDP:
		return decodeUDP
	default:
		return nil
	}
}

type IP4Packet struct {
	Version, IHL   uint8
	TOS, ECN       uint8
	Length         uint16
	Id             uint16
	Flags          uint8
	FragmentOffset uint16
	TTL            uint8
	Protocol       IPProtocol
	Checksum       uint16
	Src, Dest      net.IP
	// Options        uint32

	payload []byte
}

func (p *IP4Packet) Layer() LayerType {
	return LayerNetwork
}

func (p *IP4Packet) String() string {
	tmpl := []string{
		"IP",
		"\tSrc: %s\tDest: %s\tProtocol: %s",
		"\tTTL: %d\t\t\tId: %d\tLength: %d",
		"\tFlags: %d\t\tFragment offset: %d",
	}
	return fmt.Sprintf(
		strings.Join(tmpl, "\n"),
		p.Src.String(), p.Dest.String(),
		p.Protocol.String(),
		p.TTL, p.Id, p.Length,
		p.Flags, p.FragmentOffset,
	)
}

func (p *IP4Packet) Contents() []byte {
	return p.payload
}

func (p *IP4Packet) Payload() []byte {
	// TODO handle fragment
	return p.payload[p.IHL*4:]
}

// http://tools.ietf.org/html/rfc791#page-11
//
//   0                   1                   2                   3
//   0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |Version|  IHL  |Type of Service|          Total Length         |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |         Identification        |Flags|      Fragment Offset    |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |  Time to Live |    Protocol   |         Header Checksum       |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |                       Source Address                          |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |                    Destination Address                        |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//   |                    Options                    |    Padding    |
//   +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
func decodeIP4(raw []byte) (Impl, decodeFunc, error) {
	p := &IP4Packet{}
	ff := binary.BigEndian.Uint16(raw[6:8])

	p.payload = raw
	p.Version = uint8(raw[0]) >> 4
	p.IHL = uint8(raw[0]) & 0x0F
	p.TOS = raw[1]
	p.Length = binary.BigEndian.Uint16(raw[2:4])
	p.Id = binary.BigEndian.Uint16(raw[4:6])
	p.Flags = uint8(ff >> 13)
	p.FragmentOffset = ff & 0x1FFF
	p.TTL = raw[8]
	p.Protocol = IPProtocol(raw[9])
	p.Checksum = binary.BigEndian.Uint16(raw[10:12])
	p.Src = net.IP(raw[12:16])
	p.Dest = net.IP(raw[16:20])

	return p, p.Protocol.Decoder(), nil
}
