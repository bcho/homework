// UDP decoder.
package main

import (
	"encoding/binary"
	"fmt"
)

type UDPPackatet struct {
	Src, Dest uint16
	Length    uint16
	Checksum  uint16

	payload []byte
}

func (p *UDPPackatet) Layer() LayerType {
	return LayerTransport
}

func (p *UDPPackatet) String() string {
	return fmt.Sprintf(
		"UDP: Src: %d Dest: %d",
		p.Src, p.Dest,
	)
}

func (p *UDPPackatet) Contents() []byte {
	return p.payload
}

func (p *UDPPackatet) Payload() []byte {
	return p.payload[8:]
}

// http://tools.ietf.org/html/rfc768
//
// TODO support pesudo header
//
//  0      7 8     15 16    23 24    31
//  +--------+--------+--------+--------+
//  |     Source      |   Destination   |
//  |      Port       |      Port       |
//  +--------+--------+--------+--------+
//  |                 |                 |
//  |     Length      |    Checksum     |
//  +--------+--------+--------+--------+
//  |
//  |          data octets ...
//  +---------------- ...
func decodeUDP(raw []byte) (Impl, decodeFunc, error) {
	p := &UDPPackatet{}

	p.payload = raw
	p.Src = binary.BigEndian.Uint16(raw[0:2])
	p.Dest = binary.BigEndian.Uint16(raw[2:4])
	p.Length = binary.BigEndian.Uint16(raw[4:6])
	p.Checksum = binary.BigEndian.Uint16(raw[6:8])

	return p, nil, nil
}
