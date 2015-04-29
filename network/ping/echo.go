// Marshal & unmarshal ICMP echo message. See rfc792.
package main

import (
	"errors"
)

// Message format:
//
//  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// |     Type      |     Code      |          Checksum             |
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// |           Identifier          |        Sequence Number        |
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// |     Data ...
// +-+-+-+-+-
//
// - Id / Seq encodes with big endian.

const (
	TypeEcho   = byte(0x8)
	TypeReply  = byte(0x0)
	Code       = byte(0)
	HeaderSize = 8
)

var (
	errMessageTooShort = errors.New("message too short")
)

type Echo struct {
	Id   int
	Seq  int
	Data []byte
}

func MakeEchoMessage(Id, Seq int, Data []byte) *Echo {
	return &Echo{Id, Seq, Data}
}

func UnmarshalEchoMessage(payload []byte) (*Echo, error) {
	size := len(payload)
	if size < HeaderSize {
		return nil, errMessageTooShort
	}
	m := &Echo{
		Id:  int(payload[4])<<8 | int(payload[5]),
		Seq: int(payload[6])<<8 | int(payload[7]),
	}
	if size > HeaderSize {
		m.Data = make([]byte, size-HeaderSize)
		copy(m.Data, payload[HeaderSize:])
	}

	return m, nil
}

func (m Echo) Marshal() []byte {
	// header (8) + data (< MTU)
	payload := make([]byte, HeaderSize+len(m.Data))

	payload[0] = TypeEcho
	payload[1] = Code

	// checksum field should be zero before computing
	payload[2], payload[3] = 0x0, 0x0

	payload[4], payload[5] = byte(m.Id>>8), byte(m.Id)
	payload[6], payload[7] = byte(m.Seq>>8), byte(m.Seq)
	copy(payload[HeaderSize:], m.Data)

	// calculate the checksum
	c := checksum(payload)
	payload[2], payload[3] = byte(c), byte(c>>8)

	return payload
}

// TODO test it
func checksum(payload []byte) uint16 {
	size := len(payload)
	sum := uint32(0)

	addTo := size
	if size%2 == 1 {
		addTo = size - 1
	}
	for i := 0; i < addTo; i += 2 {
		sum += uint32(payload[i+1])<<8 | uint32(payload[i])
	}

	// padded with one octet of zeros if the length is odd
	if size%2 == 1 {
		sum += uint32(payload[addTo]) // | uint32(0) << 8
	}

	// one's complement sum
	sum = sum>>16 + sum&0xffff
	sum += sum >> 16
	return ^uint16(sum)
}
