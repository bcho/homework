package main

import (
	"crypto/des"
	"encoding/binary"
	"fmt"
	"math/rand"
	"time"
)

// How many different bits?
func diff(base, other []byte) int {
	if len(base) != len(other) {
		return 0
	}

	count := 0
	strBase := fmt.Sprintf("%064b", binary.BigEndian.Uint64(base))
	strOther := fmt.Sprintf("%064b", binary.BigEndian.Uint64(other))
	for i, _ := range strBase {
		if strBase[i] != strOther[i] {
			count = count + 1
		}
	}

	return count
}

func check(key []byte, original uint64) {
	cipher, err := des.NewCipher(key)
	if err != nil {
		panic(err)
	}

	i2b := func(i uint64) (b []byte) {
		b = make([]byte, 8)
		binary.BigEndian.PutUint64(b, i)

		return b
	}

	originalPlainText := i2b(original)
	originalCipherText := make([]byte, 8)
	cipher.Encrypt(originalCipherText, originalPlainText)

	var (
		updated          uint64
		updatedPlainText []byte
	)
	updatedCipherText := make([]byte, 8)

	sum := 0.0
	for i := 0; i < 64; i++ {
		updated = original ^ (1 << uint64(i))
		updatedPlainText = i2b(updated)
		cipher.Encrypt(updatedCipherText, updatedPlainText)
		diffed := diff(originalCipherText, updatedCipherText)
		fmt.Printf("%d -> %d\n", i+1, diffed)
		sum += float64(diffed)
	}
	fmt.Printf("original: %d\n", original)
	fmt.Printf("mean: %f\n", sum/64)
}

func main() {
	rand.Seed(time.Now().Unix())
	check([]byte("abcdefgh"), uint64(rand.Int63()))
}
