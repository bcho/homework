// Sniffer
//
// ./sniffer -interface=ean0 -pcap=offline.pcap [filter]
package main

import (
	"flag"
	"fmt"
	"io"
	"os"
	"strings"

	"github.com/google/gopacket"
	"github.com/google/gopacket/pcap"
)

const (
	NO_DEVICE          = ""
	NO_OFFLINE_FILE    = ""
	PACKET_SAMPLE_SIZE = 1600
)

var (
	device      string
	offlineFile string
)

func init() {
	flag.Usage = showUsage
	flag.StringVar(&device, "interface", NO_DEVICE, "network device (en0)")
	flag.StringVar(
		&offlineFile,
		"pcap",
		NO_OFFLINE_FILE,
		"pcap file",
	)
}

func main() {
	flag.Parse()

	filter := strings.Join(flag.Args(), " ")
	fmt.Println(filter)

	if device == NO_DEVICE && offlineFile == NO_OFFLINE_FILE {
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

	if err = handle.SetBPFFilter(filter); err != nil {
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
	fmt.Fprintf(os.Stderr, "Usage: %s [filter]\n", os.Args[0])
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
