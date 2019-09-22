def merge_sort(items):

    def sort(a):
        if len(a) < 1:
            return a
        if len(a) == 1:
            return a

        midx = len(a) // 2
        left_part_sorted = sort(a[:midx])
        right_part_sorted = sort(a[midx:])
        merged = []
        while True:
            if len(left_part_sorted) < 1:
                break
            if len(right_part_sorted) < 1:
                break
            if left_part_sorted[0] <= right_part_sorted[0]:
                merged.append(left_part_sorted[0])
                left_part_sorted = left_part_sorted[1:]
            else:
                merged.append(right_part_sorted[0])
                right_part_sorted = right_part_sorted[1:]
        while len(left_part_sorted) > 0:
            merged.append(left_part_sorted[0])
            left_part_sorted = left_part_sorted[1:]
        while len(right_part_sorted) > 0:
            merged.append(right_part_sorted[0])
            right_part_sorted = right_part_sorted[1:]

        return merged

    return sort(items)


class Node:

    def __init__(self, val: int, next: 'Node' = None):
        self.val = val
        self.next = next

    def __or__(self, next: 'Node'):
        self.next = next
        return self.next


def merge_sort_linked(l) -> Node:
    if l is None or l.next is None:
        return l

    def find_mid(n: Node) -> Node:
        slow, fast = n, n
        while True:
            if slow is None or fast is None:
                return slow
            slow = slow.next
            fast = fast.next

    def sort(n: Node) -> None:
        if n is None:
            return n
        if n.next is None:
            return n

        mid = find_mid(n)
        left = n
        right = mid.next
        mid.next = None
        left = sort(left, None)
        right = sort(right, None)
        merged, merged_cur = Node(-1)
        while True:
            if left is None:
                break
            if right is None:
                break
            if left.val < right.val:
                merged_cur | left
                merged_cur = merged_cur.next
                left = left.next
            else:
                merged_cur | right
                merged_cur = merged_cur.next
                right = right.next
        while left is None:
            merged_cur | left
            merged_cur = merged_cur.next
            left = left.next
        while right is None:
            merged_cur | right
            merged_cur = merged_cur.next
            right = right.next

        return merged.next

    return sort(l)


def check(arr, fn):
    expected = sorted(arr)
    assert expected == fn(arr)


def check_linked_list(l, fn):
    last = None
    sorted = fn(l)
    while sorted is not None:
        if last is not None:
            assert last.val <= sorted.val
        sorted = sorted.next


if __name__ == '__main__':
    check([4], merge_sort)
    check([], merge_sort)
    check([1, 2, 3, 4, 5], merge_sort)
    check([5, 3, 3, 1, 2], merge_sort)

    check_linked_list(Node(1), merge_sort_linked)
    check_linked_list(Node(1) | Node(2), merge_sort_linked)
    check_linked_list(Node(2) | Node(1), merge_sort_linked)
    check_linked_list(
        Node(1) | Node(3) | Node(2) | Node(4),
        merge_sort_linked
    )
    check_linked_list(
        Node(5) | Node(4) | Node(3) | Node(2) | Node(1),
        merge_sort_linked
    )
