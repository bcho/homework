// TCP decoder.
package main

import (
	"encoding/binary"
	"fmt"
	"strings"
)

type TCPPacket struct {
	Src, Dest  uint16
	Seq        uint32
	Ack        uint32
	DataOffset uint8
	WindowSize uint16
	Checksum   uint16
	Urgent     uint16

	NS, CWR, ECE, URG, ACK, PSH, RST, SYN, FIN bool

	payload []byte
}

func (p *TCPPacket) Layer() LayerType {
	return LayerTransport
}

func (p *TCPPacket) String() string {
	tmpl := []string{
		"TCP",
		"\tStc: %d\tDest: %d\t",
		"\tNS: %t CWR: %t ECE: %t URG: %t",
		"\tACK: %t PSH: %t RST: %t SYN: %t FIN: %t",
		"\tSeq: %d\tAck: %d",
	}
	return fmt.Sprintf(
		strings.Join(tmpl, "\n"),
		p.Src, p.Dest,
		p.NS, p.CWR, p.ECE, p.URG, p.ACK, p.PSH, p.RST, p.SYN, p.FIN,
		p.Seq, p.Ack,
	)
}

func (p *TCPPacket) Contents() []byte {
	return p.payload
}

func (p *TCPPacket) Payload() []byte {
	return p.payload[p.DataOffset*4:]
}

// http://en.wikipedia.org/wiki/Transmission_Control_Protocol#TCP_segment_structure
func decodeTCP(raw []byte) (Impl, decodeFunc, error) {
	p := &TCPPacket{}

	p.payload = raw
	p.Src = binary.BigEndian.Uint16(raw[0:2])
	p.Dest = binary.BigEndian.Uint16(raw[2:4])
	p.Seq = binary.BigEndian.Uint32(raw[4:8])
	p.Ack = binary.BigEndian.Uint32(raw[8:12])
	p.DataOffset = raw[12] >> 4
	p.NS = raw[12]&0x01 != 0
	p.CWR = raw[13]&0x80 != 0
	p.ECE = raw[13]&0x40 != 0
	p.URG = raw[13]&0x20 != 0
	p.ACK = raw[13]&0x10 != 0
	p.PSH = raw[13]&0x08 != 0
	p.RST = raw[13]&0x04 != 0
	p.SYN = raw[13]&0x02 != 0
	p.FIN = raw[13]&0x01 != 0
	p.WindowSize = binary.BigEndian.Uint16(raw[14:16])
	p.Checksum = binary.BigEndian.Uint16(raw[16:18])
	p.Urgent = binary.BigEndian.Uint16(raw[18:20])

	return p, nil, nil
}
