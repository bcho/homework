// A simple icmp decoder.
package main

import (
	"encoding/binary"
	"fmt"
)

type ICMPPacket struct {
	Type     uint8
	Code     uint8
	Checksum uint16

	payload []byte
}

func (p *ICMPPacket) Layer() LayerType {
	// FIXME should be network layer
	return LayerTransport
}

func (p *ICMPPacket) String() string {
	return fmt.Sprintf(
		"ICMP Type: %d Code: %d",
		p.Type, p.Code,
	)
}

func (p *ICMPPacket) Contents() []byte {
	return p.payload
}

// The rest of the header (data).
func (p *ICMPPacket) Payload() []byte {
	return p.payload[4:]
}

// http://en.wikipedia.org/wiki/Internet_Control_Message_Protocol#Header
//
// 0                   1                   2                   3
// 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// |     Type      |     Code      |          Checksum             |
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// |     Data ...
// +-------- ...
func decodeICMP(raw []byte) (Impl, decodeFunc, error) {
	p := &ICMPPacket{}

	p.payload = raw
	p.Type = raw[0]
	p.Code = raw[1]
	p.Checksum = binary.BigEndian.Uint16(raw[2:4])

	return p, nil, nil
}
