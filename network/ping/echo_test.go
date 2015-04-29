package main

import (
	"testing"
)

func TestMarshalAndUnmarshal(t *testing.T) {
	expectedId, expectedSeq := 1, 1
	expectedData := []byte("hello world")
	m := MakeEchoMessage(expectedId, expectedSeq, expectedData)

	encoded := m.Marshal()
	decoded, err := UnmarshalEchoMessage(encoded)
	if err != nil {
		t.Error(err)
	}

	if decoded.Id != expectedId {
		t.Errorf("id")
	}
	if decoded.Seq != expectedSeq {
		t.Errorf("seq")
	}
	if string(decoded.Data) != string(expectedData) {
		t.Errorf("data")
	}
}

func TestChecksum(t *testing.T) {
	testcases := [][]byte{
		[]byte("hello world"),
		[]byte("foobar"),
		[]byte("123456"),
	}

	correctChecksum := func(b []byte) uint16 {
		csumcv := len(b) - 1 // checksum coverage
		s := uint32(0)
		for i := 0; i < csumcv; i += 2 {
			s += uint32(b[i+1])<<8 | uint32(b[i])
		}
		if csumcv&1 == 0 {
			s += uint32(b[csumcv])
		}
		s = s>>16 + s&0xffff
		s = s + s>>16
		return ^uint16(s)
	}

	for _, testcase := range testcases {
		if checksum(testcase) != correctChecksum(testcase) {
			t.Errorf("checksum")
		}
	}
}
