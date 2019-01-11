package main

import "fmt"

type f func(height []int) int

func maxArea_n2(height []int) int {
	min := func(a, b int) int {
		if a < b {
			return a
		}
		return b
	}

	if len(height) == 2 {
		return min(height[0], height[1])
	}

	var (
		max int
	)
	for i := 0; i < len(height); i++ {
		for j := i + 1; j < len(height); j++ {
			w := min(height[i], height[j])
			d := w * (j - i)
			if d > max {
				max = d
			}
		}
	}

	return max
}

func maxArea_greedy(height []int) int {
	max := 0
	i := 0
	j := len(height) - 1
	for j > i {
		var (
			h int
			w = j - i
		)
		if height[j] > height[i] {
			h = height[i]
			i = i + 1
		} else {
			h = height[j]
			j = j - 1
		}
		if d := h * w; d > max {
			max = d
		}
	}

	return max
}

func main() {
	fs := map[string]f{
		"n2":     maxArea_n2,
		"greedy": maxArea_greedy,
	}

	cases := []struct {
		height   []int
		expected int
	}{
		{[]int{1, 1}, 1},
		{[]int{1, 2}, 1},
		{[]int{2, 4}, 2},
		{[]int{1, 2, 4}, 2},
		{[]int{1, 8, 6, 2, 5, 4, 8, 3, 7}, 49},
	}
	for name, f := range fs {
		fmt.Println(name + ":")
		for i, c := range cases {
			rv := f(c.height)
			if rv == c.expected {
				fmt.Printf("passed: %d\n", i)
			} else {
				fmt.Printf("failed: %d %d %d\n", i, rv, c.expected)
			}
		}
	}
}
