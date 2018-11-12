package main

import "fmt"

// in merge sort ways... O((m+n)/2)
func findMedianSortedArrays(nums1 []int, nums2 []int) float64 {
	var idxm0, idxm1, m0, m1 int
	d := len(nums1) + len(nums2)
	if d%2 == 0 {
		idxm1 = d / 2
		idxm0 = idxm1 - 1
	} else {
		idxm1 = (d - 1) / 2
		idxm0 = (d - 1) / 2
	}

	threw := 0
	idx1, idx2 := 0, 0
	for {
		nums1Empty := idx1 >= len(nums1)
		nums2Empty := idx2 >= len(nums2)
		useNums1 := false
		switch {
		case nums1Empty && nums2Empty:
			panic("should not be both empty")
		case nums2Empty:
			useNums1 = true
		case nums1Empty:
			useNums1 = false
		default:
			useNums1 = nums1[idx1] < nums2[idx2]
		}
		if threw == idxm0 {
			if useNums1 {
				m0 = nums1[idx1]
			} else {
				m0 = nums2[idx2]
			}
		}
		if threw == idxm1 {
			if useNums1 {
				m1 = nums1[idx1]
			} else {
				m1 = nums2[idx2]
			}
			return float64(m0+m1) / 2
		}
		if useNums1 {
			idx1 = idx1 + 1
		} else {
			idx2 = idx2 + 1
		}
		threw = threw + 1
	}
}

func main() {
	cases := []struct {
		nums1    []int
		nums2    []int
		expexted float64
	}{
		{[]int{}, []int{1, 2}, 1.5},
		{[]int{1, 2}, []int{}, 1.5},
		{[]int{1, 2}, []int{1, 2}, 1.5},
		{[]int{1, 2, 3}, []int{4, 5, 6}, 3.5},
		{[]int{1, 2, 3}, []int{4, 5}, 3},
		{[]int{1, 2, 3}, []int{4, 4, 4, 4, 4}, 4},
	}
	for i, c := range cases {
		rv := findMedianSortedArrays(c.nums1, c.nums2)
		if compareFloat64(rv, c.expexted) {
			fmt.Printf("passed: %d\n", i)
		} else {
			fmt.Printf("failed: %d\n%.4f %.4f\n%v\n", i, rv, c.expexted, c)
		}
		fmt.Println()
	}
}

func compareFloat64(a, b float64) bool {
	if d := a - b; d < 0 {
		return -d < 0.001
	} else {
		return d < 0.001
	}
}
