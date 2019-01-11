package main

import "fmt"

type ListNode struct {
	Val  int
	Next *ListNode
}

func ListNodeFromSlice(is []int) *ListNode {
	var (
		head *ListNode
		last *ListNode
	)
	for _, i := range is {
		p := &ListNode{
			Val:  i,
			Next: nil,
		}
		if head == nil {
			head = p
			last = p
		} else {
			last.Next = p
			last = p
		}
	}

	return head
}

func (l *ListNode) String() string {
	if l == nil {
		return "<nil>"
	}
	return fmt.Sprintf("%d->%s", l.Val, l.Next)
}

func (l *ListNode) IsEqual(other *ListNode) bool {
	return l.String() == other.String()
}

func reverseGroup(head *ListNode, k int) *ListNode {
	if k < 2 {
		return head
	}

	var (
		sentinel                = &ListNode{Next: head}
		groupSentinel           = sentinel
		p             *ListNode = groupSentinel.Next
		pcnt          int       = 1
	)
	for {
		if pcnt == k {
			groupSentinel = p
			p = groupSentinel.Next
			pcnt = 1
			continue
		}

		if p == nil || p.Next == nil {
			p = groupSentinel.Next
			for {
				if p == nil || p.Next == nil {
					return sentinel.Next
				}

				tmp := groupSentinel.Next
				groupSentinel.Next = p.Next
				p.Next = groupSentinel.Next.Next
				groupSentinel.Next.Next = tmp
			}
		}

		tmp := groupSentinel.Next
		groupSentinel.Next = p.Next
		p.Next = groupSentinel.Next.Next
		groupSentinel.Next.Next = tmp
		pcnt = pcnt + 1
	}
}

func main() {
	cases := []struct {
		x        []int
		k        int
		expected []int
	}{
		{[]int{1, 2, 3, 4, 5}, 1, []int{1, 2, 3, 4, 5}},
		{[]int{1, 2, 3, 4, 5}, 2, []int{2, 1, 4, 3, 5}},
		{[]int{1, 2, 3, 4, 5}, 3, []int{3, 2, 1, 4, 5}},
		{[]int{1, 2, 3, 4, 5}, 4, []int{4, 3, 2, 1, 5}},
		{[]int{1, 2, 3, 4, 5}, 5, []int{5, 4, 3, 2, 1}},
		{[]int{1, 2, 3}, 4, []int{1, 2, 3}},
	}
	for i, c := range cases {
		reversed := reverseGroup(ListNodeFromSlice(c.x), c.k)
		expected := ListNodeFromSlice(c.expected)
		if reversed.IsEqual(expected) {
			fmt.Printf("%d passed\n", i)
		} else {
			fmt.Printf("%d failed: %s, %s\n", i, reversed, expected)
		}
	}
}
