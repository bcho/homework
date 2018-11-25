package main

import "fmt"

type f func(s string, numRows int) string

func convert_basic(s string, numRows int) string {
	if numRows < 1 {
		return ""
	}
	if s == "" {
		return ""
	}

	rows := make([]string, numRows)
	rc := 0
	mode := 1
	for _, c := range s {
		if rc < 0 {
			rc = 0
		} else if rc >= numRows {
			rc = 0
		}

		rows[rc] = rows[rc] + string(c)
		rc = rc + mode
		if rc >= numRows {
			rc = numRows - 2
			mode = -1
		} else if rc < 0 {
			rc = 1
			mode = 1
		}
	}

	rv := ""
	for _, row := range rows {
		rv = rv + row
	}

	return rv
}

func main() {
	fs := map[string]f{
		"basic": convert_basic,
	}

	cases := []struct {
		s        string
		numRows  int
		expected string
	}{
		{"", 1, ""},
		{"a", 1, "a"},
		{"a", 2, "a"},
		{"ab", 2, "ab"},
		{"ab", 1, "ab"},
		{"abc", 2, "acb"},
		{"PAYPALISHIRING", 3, "PAHNAPLSIIGYIR"},
		{"PAYPALISHIRING", 4, "PINALSIGYAHRPI"},
	}
	for name, f := range fs {
		fmt.Println(name + ":")
		for i, c := range cases {
			rv := f(c.s, c.numRows)
			if rv == c.expected {
				fmt.Printf("passed: %d\n", i)
			} else {
				fmt.Printf("failed: %d %s %s\n", i, rv, c.expected)
			}
		}
	}
}
