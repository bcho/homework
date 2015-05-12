package main

import (
	"encoding/json"
	"fmt"
	"log"
	"net/http"
	"sync"
)

type packetsPool struct {
	sync.Mutex

	packets []*packet
}

func newPacketsPool() *packetsPool {
	return &packetsPool{}
}

func (p *packetsPool) add(packet *packet) {
	p.Lock()
	p.packets = append(p.packets, packet)
	p.Unlock()
}

func (p *packetsPool) toJSON() ([]byte, error) {
	return json.Marshal(p.packets)
}

func httpHandler(port int, packetChan chan *packet, errChan chan error) {
	packetsPool := newPacketsPool()

	http.HandleFunc("/_packet", func(w http.ResponseWriter, r *http.Request) {
		marshaled, err := packetsPool.toJSON()
		if err != nil {
			errChan <- err
			return
		}
		w.Header().Set("Content-Type", "application/json")
		w.Write(marshaled)
	})

	// TODO serve files
	http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
		http.ServeFile(w, r, "index.html")
	})
	http.HandleFunc("/jquery.js", func(w http.ResponseWriter, r *http.Request) {
		http.ServeFile(w, r, "static/jquery.js")
	})

	go (func() {
		for {
			select {
			case err := <-errChan:
				log.Print(err)
			case packet := <-packetChan:
				log.Printf(
					"got new packet: %s:%s",
					packet.Type,
					string(packet.Content),
				)
				packetsPool.add(packet)
			}
		}
	})()

	log.Fatal(http.ListenAndServe(fmt.Sprintf(":%d", port), nil))
}
