// Unknown packet decoder.
package main

type UnknownPacket struct {
	payload []byte
}

func (p *UnknownPacket) Layer() LayerType {
	return LayerUnknown
}

func (p *UnknownPacket) String() string {
	return "Unknown"
}

func (p *UnknownPacket) Contents() []byte {
	return p.payload
}

func (p *UnknownPacket) Payload() []byte {
	return nil
}

func decodeUnknown(raw []byte) (Impl, decodeFunc, error) {
	return &UnknownPacket{raw}, nil, nil
}
