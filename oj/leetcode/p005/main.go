package main

import "fmt"

type f func(s string) string

func longestPalindrome_brute(s string) string {
	var isPalindrome func(i, j int) bool
	isPalindrome = func(i, j int) bool {
		if i >= j {
			return true
		}
		if s[i] != s[j] {
			return false
		}
		return isPalindrome(i+1, j-1)
	}

	for n := len(s); n >= 1; n-- {
		for i := 0; i+n <= len(s); i++ {
			if isPalindrome(i, i+n-1) {
				return s[i : i+n]
			}
		}
	}

	return ""
}

func longestPalindrome_dp(s string) string {
	if len(s) < 1 {
		return ""
	}
	if len(s) < 2 {
		return s
	}

	p := make([][]int8, len(s))
	for i := 0; i < len(s); i++ {
		p[i] = make([]int8, len(s))
	}

	var r func(i, j int) bool
	r = func(i, j int) bool {
		if i >= j {
			return true
		}
		if p[i][j] == 0 {
			rv := true
			if s[i] != s[j] {
				rv = false
			} else {
				rv = r(i+1, j-1)
			}
			if rv {
				p[i][j] = 1
			} else {
				p[i][j] = 2
			}
		}
		return p[i][j] == 1
	}

	maxLen, from, to := 1, 0, 0
	for i := 0; i < len(s); i++ {
		for j := i; j < len(s); j++ {
			if !r(i, j) {
				continue
			}

			newLen := j - i + 1
			if newLen <= maxLen {
				continue
			}
			maxLen, from, to = newLen, i, j
		}
	}
	return s[from : to+1]
}

func main() {
	fs := map[string]f{
		"brute": longestPalindrome_brute,
		"dp":    longestPalindrome_dp,
	}

	cases := []struct {
		s        string
		expected string
	}{
		{"", ""},
		{"a", "a"},
		{"ab", "a"},
		{"cbbd", "bb"},
		{"babad", "bab"},
		{"aaa", "aaa"},
		{"abaab", "baab"},
	}
	for name, f := range fs {
		fmt.Println(name + ":")
		for i, c := range cases {
			rv := f(c.s)
			if rv == c.expected {
				fmt.Printf("passed: %d\n", i)
			} else {
				fmt.Printf("failed: %d %s %s\n", i, rv, c.expected)
			}
		}
	}
}
