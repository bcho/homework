package main

import "fmt"

func divide(dividend int, divisor int) int {
	minusDividend := false
	minusDivisor := false

	if dividend < 0 {
		minusDividend = true
		dividend = -dividend
	}
	if divisor < 0 {
		minusDivisor = true
		divisor = -divisor
	}

	var (
		rv int
		p  int
	)
	for {
		p = p + divisor
		if p > dividend {
			break
		}
		rv = rv + 1
		if minusDividend == minusDivisor && rv >= 2147483647 {
			break
		}
	}

	if minusDividend != minusDivisor {
		rv = rv * -1
	}

	return rv
}

func main() {
	cases := []struct {
		dividend int
		divisor  int
		expected int
	}{
		{10, 3, 3},
		{7, -3, -2},
		{0, -3, 0},
		{0, 3, 0},
		{1, 1, 1},
		{-2147483648, -1, 2147483647},
		{-2147483648, 1, -2147483648},
	}

	for i, c := range cases {
		rv := divide(c.dividend, c.divisor)
		if rv == c.expected {
			fmt.Printf("passed: %d\n", i)
		} else {
			fmt.Printf("failed: %d %d %d\n", i, c.expected, rv)
		}
	}
}
