package main

import "fmt"

type f func(s string, p string) bool

func isMatch_basic(s string, p string) bool {
	if s == "" {
		if p == "" {
			return true
		}

		if p[0] == '.' {
			return true
		}

		return false
	}

	si := 0
	pi := 0

	advanceP := func(force bool) {
		pi = pi + 1
		if pi >= len(p) {
			return
		}

		if p[pi] == '*' && !force {
			pi = pi - 1
			return
		}

		if p[pi] == '*' && force {
			c := p[pi-1]
			pi = pi + 1
			for pi < len(p) {
				if p[pi] != c {
					break
				}
				pi = pi + 1
			}
			return
		}
	}

	for {
		if si >= len(s) {
			break
		}
		if pi >= len(p) {
			break
		}

		if p[pi] == '.' {
			si = si + 1
			advanceP(si >= len(s))
		} else if s[si] == p[pi] {
			si = si + 1
			advanceP(si >= len(s))
		} else {
			advanceP(true)
		}
	}

	return si >= len(s) && pi >= len(p)
}

func main() {
	fs := map[string]f{
		"basic": isMatch_basic,
	}

	cases := []struct {
		s        string
		p        string
		expected bool
	}{
		{"", "", true},
		{"", "x", false},
		{"", ".*", true},
		{"", ".", true},
		{"ab", ".*c", false},
		{"aa", "a", false},
		{"aa", "a*", true},
		{"ab", ".*", true},
		{"aaa", "a*a", true},
		{"aab", "c*a*b*", true},
		{"aaa", "aaaa", false},
		{"mississippi", "mis*is*p*.", false},
	}
	for name, f := range fs {
		fmt.Println(name + ":")
		for i, c := range cases {
			rv := f(c.s, c.p)
			if rv == c.expected {
				fmt.Printf("passed: %d\n", i)
			} else {
				fmt.Printf("failed: %d %v %v\n", i, rv, c.expected)
			}
		}
	}
}
