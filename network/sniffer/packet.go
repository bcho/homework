package main

import (
	"strings"
)

// A network packet.
type Packet struct {
	payload []byte

	LinkLayer        Impl
	NetworkLayer     Impl
	TransportLayer   Impl
	ApplicationLayer Impl
}

// Create a packet from raw input.
func CreatePacketFromByte(payload []byte) *Packet {
	p := &Packet{payload: payload}

	setLayer := func(impl Impl) {
		switch impl.Layer() {
		case LayerLink:
			p.LinkLayer = impl
		case LayerNetwork:
			p.NetworkLayer = impl
		case LayerTransport:
			p.TransportLayer = impl
		case LayerApplication:
			p.ApplicationLayer = impl
		}
	}

	var (
		impl                 Impl
		decoder, nextDecoder decodeFunc
		err                  error
	)
	for _, decoder = range decoders {
		impl, nextDecoder, err = decoder(payload)
		// Try another decoder.
		if err != nil {
			continue
		}

		// Start from this decoder.
		setLayer(impl)
		break
	}

	decoder = nextDecoder
	payload = impl.Payload()
	for {
		// No more decoder.
		if decoder == nil {
			break
		}
		impl, nextDecoder, err = decoder(payload)
		if err != nil {
			break
		}

		setLayer(impl)
		decoder = nextDecoder
		payload = impl.Payload()
	}

	return p
}

// Get all layers of this packet.
func (p *Packet) Layers() []Impl {
	var layers []Impl

	orders := []Impl{
		p.LinkLayer,
		p.NetworkLayer,
		p.TransportLayer,
		p.ApplicationLayer,
	}
	for _, layer := range orders {
		if layer != nil {
			layers = append(layers, layer)
		}
	}

	return layers
}

// The entire content of the packet.
func (p *Packet) Contents() []byte {
	return p.payload
}

// Compile into human readable format.
func (p *Packet) String() string {
	s := []string{LINE_DELIM}
	for _, layer := range p.Layers() {
		s = append(s, layer.String())
	}
	s = append(s, LINE_DELIM)
	return strings.Join(s, "\n")
}
