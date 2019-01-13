package main

import (
	"fmt"
	"sort"
)

type f func(s string, words []string) []int

// TLE
func findSubstring_invert(s string, words []string) []int {
	sidx := map[int][]int{}
	for idx := 0; idx < len(s); idx++ {
		for widx, w := range words {
			if len(s)-idx < len(w) {
				continue
			}
			matched := true
			for j := 0; j < len(w); j++ {
				if w[j] != s[idx+j] {
					matched = false
					break
				}
			}
			if matched {
				sidx[idx] = append(sidx[idx], widx)
			}
		}
	}

	var (
		rv           = map[int]struct{}{}
		searchSubSet func(int, int, map[int]struct{})
	)

	searchSubSet = func(startIdx, idx int, wused map[int]struct{}) {
		wset, exists := sidx[idx]
		if !exists {
			return
		}

		for _, widx := range wset {
			if _, used := wused[widx]; used {
				continue
			}

			if len(wused) == len(words)-1 {
				rv[startIdx] = struct{}{}
				return
			}

			wused[widx] = struct{}{}
			searchSubSet(
				startIdx,
				idx+len(words[widx]),
				wused,
			)
			delete(wused, widx)
		}
	}

	for idx := 0; idx < len(s); idx++ {
		wused := map[int]struct{}{}
		searchSubSet(idx, idx, wused)
	}

	var rvs []int
	for idx := range rv {
		rvs = append(rvs, idx)
	}

	return rvs
}

func check(a []int, b []int) bool {
	if len(a) != len(b) {
		return false
	}

	sort.IntSlice(a).Sort()
	sort.IntSlice(b).Sort()

	for i := 0; i < len(a); i++ {
		if a[i] != b[i] {
			return false
		}
	}

	return true
}

func main() {
	fs := map[string]f{
		"invert": findSubstring_invert,
	}

	cases := []struct {
		s        string
		words    []string
		expected []int
	}{
		{"abc", []string{"abc"}, []int{0}},
		{"barfoothefoobarman", []string{"foo", "bar"}, []int{0, 9}},
		{"abc", []string{"abcd"}, []int{}},
		{
			"wordgoodgoodgoodbestword",
			[]string{"word", "good", "best", "good"},
			[]int{8},
		},
		{
			"wordgoodgoodgoodbestword",
			[]string{"word", "good", "best", "word"},
			[]int{},
		},
	}

	for name, f := range fs {
		fmt.Println(name + ":")
		for idx, c := range cases {
			rv := f(c.s, c.words)
			if check(c.expected, rv) {
				fmt.Printf("%d passed\n", idx)
			} else {
				fmt.Printf("%d failed: %v %v\n", idx, c.expected, rv)
			}
		}
	}
}
