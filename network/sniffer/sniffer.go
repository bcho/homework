// Sniffer
//
// ./sniffer -interface=ean0 [offline.pcap]
package main

import (
	"flag"
	"fmt"
	"io"
	"os"

	"github.com/google/gopacket"
	"github.com/google/gopacket/pcap"
)

const (
	NO_DEVICE          = ""
	PACKET_SAMPLE_SIZE = 1600
)

var device string

func init() {
	flag.Usage = showUsage
	flag.StringVar(&device, "interface", NO_DEVICE, "network device (en0)")
}

func main() {
	flag.Parse()

	offlineFile := flag.Arg(0)

	if device == NO_DEVICE && offlineFile == "" {
		flag.Usage()
		os.Exit(1)
	}

	var (
		handle *pcap.Handle
		err    error
	)

	if hasFile(offlineFile) {
		fmt.Printf("Reading packet from %s:\n", offlineFile)
		handle, err = pcap.OpenOffline(offlineFile)
	} else {
		fmt.Printf("Reading packet from %s:\n", device)
		handle, err = pcap.OpenLive(
			device,
			PACKET_SAMPLE_SIZE,
			true,
			pcap.BlockForever,
		)
	}
	if err != nil {
		panic(err)
	}

	for {
		packet, ci, err := handle.ReadPacketData()
		if err == io.EOF {
			break
		}
		if err != nil {
			panic(err)
		}
		handlePacket(packet, ci)
	}
}

func showUsage() {
	fmt.Fprintf(os.Stderr, "Usage: %s [file]\n", os.Args[0])
	flag.PrintDefaults()
}

func hasFile(file string) bool {
	_, err := os.Stat(file)
	return err == nil
}

func handlePacket(data []byte, ci gopacket.CaptureInfo) {
	packet := CreatePacketFromByte(data)
	fmt.Println(packet.String())
}
