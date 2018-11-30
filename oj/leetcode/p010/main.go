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

func isMatch_dfs(s string, p string) bool {
	hasStar := len(p) > 1 && p[1] == '*'

	if s == "" {
		if p == "" {
			// both empty
			return true
		}

		if hasStar && isMatch_dfs(s, p[2:]) {
			// skip the star
			return true
		}

		return false
	}
	if p == "" {
		return false
	}

	if s[0] == p[0] || p[0] == '.' {
		if hasStar {
			if isMatch_dfs(s[1:], p) {
				return true
			}
			if isMatch_dfs(s[1:], p[2:]) {
				return true
			}
			if isMatch_dfs(s, p[2:]) {
				// try skip the star
				return true
			}
		} else {
			if isMatch_dfs(s[1:], p[1:]) {
				return true
			}
		}

		return false
	} else {
		if hasStar {
			return isMatch_dfs(s, p[2:])
		}

		return false
	}
}

func main() {
	fs := map[string]f{
		"basic": isMatch_basic,
		"dfs":   isMatch_dfs,
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
		{"aaa", "ab*a*c*a", true},
		{"mississippi", "mis*is*p*.", false},
		{"a", "a*a", true},
		{"bbbba", ".*a*a", true},
		{"a", ".*..", false},
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
