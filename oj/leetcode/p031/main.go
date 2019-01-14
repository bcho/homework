package main

import "fmt"

func nextPermutation(nums []int) {
	if len(nums) < 2 {
		return
	}

	k := len(nums) - 2
	for ; k >= 0 && nums[k+1] <= nums[k]; k-- {
	}
	if k >= 0 {
		j := len(nums) - 1
		for ; j >= k+1; j-- {
			if nums[j] > nums[k] {
				nums[k], nums[j] = nums[j], nums[k]
				break
			}
		}
	}

	p := len(nums) - 1 + k + 1
	for j := k + 1; j <= p/2; j++ {
		nums[j], nums[p-j] = nums[p-j], nums[j]
	}
}

func check(a, b []int) bool {
	if len(a) != len(b) {
		return false
	}

	for i := 0; i < len(a); i++ {
		if a[i] != b[i] {
			return false
		}
	}

	return true
}

func main() {
	cases := []struct {
		input    []int
		expected []int
	}{
		{[]int{1, 2, 3}, []int{1, 3, 2}},
		{[]int{3, 2, 1}, []int{1, 2, 3}},
		{[]int{3, 2, 4, 1}, []int{3, 4, 1, 2}},
		{[]int{1, 3, 2}, []int{2, 1, 3}},
	}

	for idx, c := range cases {
		nextPermutation(c.input)
		if check(c.input, c.expected) {
			fmt.Printf("%d passed\n", idx)
		} else {
			fmt.Printf("%d failed %v %v\n", idx, c.input, c.expected)
		}
	}
}
