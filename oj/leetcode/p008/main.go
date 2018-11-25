package main

import "fmt"

type f func(string) int

func myAtoi_basic(s string) int {
	rv := 0
	sign := 1
	i := 0
	for i < len(s) {
		if s[i] != ' ' {
			break
		}
		i = i + 1
	}
	if i >= len(s) {
		return 0
	}
	switch s[i] {
	case '-':
		sign = -1
		i = i + 1
	case '+':
		sign = 1
		i = i + 1
	}
forloop:
	for i < len(s) {
		switch s[i] {
		case '0', '1', '2', '3', '4', '5', '6', '7', '8', '9':
			rv = rv*10 + int(s[i]-'0')
			adjusted := rv * sign
			if adjusted >= 2147483647 {
				return 2147483647
			}
			if adjusted <= -2147483648 {
				return -2147483648
			}
		default:
			break forloop
		}
		i = i + 1
	}

	return rv * sign
}

func main() {
	fs := map[string]f{
		"basic": myAtoi_basic,
	}

	cases := []struct {
		s        string
		expected int
	}{
		{"", 0},
		{"42", 42},
		{"   -42", -42},
		{"4193 with words", 4193},
		{"words and 987", 0},
		{"-91283472332", -2147483648},
	}
	for name, f := range fs {
		fmt.Println(name + ":")
		for i, c := range cases {
			rv := f(c.s)
			if rv == c.expected {
				fmt.Printf("passed: %d\n", i)
			} else {
				fmt.Printf("failed: %d %d %d\n", i, rv, c.expected)
			}
		}
	}
}
