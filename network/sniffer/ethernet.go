// Ethernet decoder.
package main

import (
	"encoding/binary"
	"fmt"
	"net"
)

type EthernetType uint16

func (t EthernetType) String() string {
	var typeName string
	switch t {
	case EthernetIP4:
		typeName = "IP4"
	default:
		typeName = "UNKNOWN"
	}
	return fmt.Sprintf(
		"%s (0x%04x)",
		typeName,
		uint16(t), // have to convert into uint16 explicitly?
	)
}

func (t EthernetType) Decoder() decodeFunc {
	switch t {
	case EthernetIP4:
		return decodeIP4
	default:
		return nil
	}
}

type Ethernet struct {
	Dest net.HardwareAddr
	Src  net.HardwareAddr
	Type EthernetType

	payload []byte
}

func (p *Ethernet) Layer() LayerType {
	return LayerLink
}

func (p *Ethernet) String() string {
	return fmt.Sprintf(
		"Ethernet Dest: %s Src: %s Type: %s",
		p.Dest.String(),
		p.Src.String(),
		p.Type.String(),
	)
}

func (p *Ethernet) Contents() []byte {
	return p.payload
}

func (p *Ethernet) Payload() []byte {
	return p.payload[14:]
}

// http://en.wikipedia.org/wiki/Ethernet_frame#Structure
//
// - no preamble / SFD / FCS (handle by hardware)
//
// +---------+---------+------+------------------------------------
// | dest    | src     | type | payload
// +---------+---------+------+------------------------------------
func decodeEthernet(raw []byte) (Impl, decodeFunc, error) {
	if len(raw) < 14 {
		return nil, nil, errDecodeFailed
	}

	dest := net.HardwareAddr(raw[0:6])
	src := net.HardwareAddr(raw[6:12])
	type_ := EthernetType(binary.BigEndian.Uint16(raw[12:14]))
	p := &Ethernet{dest, src, type_, raw}

	return p, p.Type.Decoder(), nil
}
