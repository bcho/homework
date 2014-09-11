// This program is used to demonstraion dead-lock.
// run with: go run -race race_condition.go

package main

import (
	"fmt"
	"time"
)

var globalInt = 1

func updateGlobalInt() {
	for i := 0; i < 10000000; i++ {
		globalInt += 1
	}
}

func main() {
	fmt.Printf("Global int: %d\n", globalInt)

	for i := 0; i < 10; i++ {
		go updateGlobalInt()
	}

	time.Sleep(4 * time.Second)
	fmt.Printf("Global int: %d\n", globalInt)
}
