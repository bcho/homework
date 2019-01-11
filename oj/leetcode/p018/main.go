package main

import (
	"fmt"
	"sort"
)

type f func(nums []int, target int) [][]int

func fourSum_n3(nums []int, target int) [][]int {
	sort.IntSlice(nums).Sort()

	var rv [][]int

	for a := 0; a < len(nums)-3; {
		na := nums[a]
		for b := a + 1; b < len(nums)-2; {
			nb := nums[b]
			wanted := target - (na + nb)
			c, d := b+1, len(nums)-1
			for c < d {
				nc, nd := nums[c], nums[d]
				now := nc + nd
				if now == wanted {
					rv = append(rv, []int{na, nb, nc, nd})
					for c < len(nums) && nums[c] == nc {
						c = c + 1
					}
					for d > 0 && nums[d] == nd {
						d = d - 1
					}
				} else if now > wanted {
					d = d - 1
				} else if now < wanted {
					c = c + 1
				}
			}

			for b < len(nums)-2 && nums[b] == nb {
				b = b + 1
			}
		}
		for a < len(nums)-3 && nums[a] == na {
			a = a + 1
		}
	}

	return rv
}

func match(a [][]int, b [][]int) bool {
	if len(a) != len(b) {
		return false
	}
	for i := range a {
		sort.IntSlice(a[i]).Sort()
		sort.IntSlice(b[i]).Sort()
	}

	sort.SliceStable(a, func(i, j int) bool {
		xi, xj := a[i], a[j]
		for d := range xi {
			if xi[d] < xj[d] {
				return true
			}
			if xi[d] > xj[d] {
				return false
			}
		}
		return true
	})
	sort.SliceStable(b, func(i, j int) bool {
		xi, xj := b[i], b[j]
		for d := range xi {
			if xi[d] < xj[d] {
				return true
			}
			if xi[d] > xj[d] {
				return false
			}
		}
		return true
	})

	for i := range a {
		xa, xb := a[i], b[i]
		for d := range xa {
			if xa[d] != xb[d] {
				return false
			}
		}
	}

	return true
}

func main() {
	fs := map[string]f{
		"n3": fourSum_n3,
	}

	cases := []struct {
		nums     []int
		target   int
		expected [][]int
	}{
		{
			nums:   []int{1, 0, -1, 0, -2, 2},
			target: 0,
			expected: [][]int{
				{-1, 0, 0, 1},
				{-2, -1, 1, 2},
				{-2, 0, 0, 2},
			},
		},
		{
			nums:     []int{0, 0, 0, 0},
			target:   0,
			expected: [][]int{{0, 0, 0, 0}},
		},
		{
			nums:   []int{-3, -2, -1, 0, 0, 1, 2, 3},
			target: 0,
			expected: [][]int{
				{-3, -2, 2, 3},
				{-3, -1, 1, 3},
				{-3, 0, 0, 3},
				{-3, 0, 1, 2},
				{-2, -1, 0, 3},
				{-2, -1, 1, 2},
				{-2, 0, 0, 2},
				{-1, 0, 0, 1},
			},
		},
	}
	for name, f := range fs {
		fmt.Println(name + ":")
		for i, c := range cases {
			rv := f(c.nums, c.target)
			if match(rv, c.expected) {
				fmt.Printf("passed: %d\n", i)
			} else {
				fmt.Printf("failed: %d \n%v \n%v", i, rv, c.expected)
			}
		}
	}
}
