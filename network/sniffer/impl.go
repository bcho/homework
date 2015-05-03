// Protocol implementation.
package main

type Impl interface {
	// Implementation layer.
	Layer() LayerType

	// Compile into human readable format.
	String() string

	// The entire content of the packet.
	Contents() []byte

	// The entire payload of the packet. (Without header.)
	Payload() []byte
}
