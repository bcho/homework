from typing import List


def qsort_recursive(items: List[int]):

    def do_sort(lidx: int, ridx: int):
        if lidx >= ridx:
            # done
            return

        _lidx, _ridx = lidx, ridx
        pidx, lidx = lidx, lidx + 1
        while lidx <= ridx:
            # keep looping while lefti pointer is behind the right pointer
            if items[pidx] < items[lidx]:
                # left side value is larger than the pivot, swap to right
                items[ridx], items[lidx] = items[lidx], items[ridx]
                ridx -= 1
            else:
                # left side value is smaller than or equal to the pivot,
                # advance the left pointer
                lidx += 1

        # by now, all value at the right pointer and left to the right pointer
        # are smaller than or equal to the pivot value, so swap the pivot to
        # this place
        items[pidx], items[ridx] = items[ridx], items[pidx]

        do_sort(_lidx, ridx - 1)
        do_sort(ridx + 1, _ridx)

    do_sort(0, len(items) - 1)


def qsort_iterative(items: List[int]):
    idx_stack = [(0, len(items) - 1)]

    while len(idx_stack) > 0:
        lidx, ridx = idx_stack.pop()
        if lidx >= ridx:
            continue

        _lidx, _ridx = lidx, ridx
        pidx, lidx = lidx, lidx + 1
        while lidx <= ridx:
            if items[pidx] < items[lidx]:
                items[ridx], items[lidx] = items[lidx], items[ridx]
                ridx -= 1
            else:
                lidx += 1
        items[pidx], items[ridx] = items[ridx], items[pidx]

        idx_stack.append((_lidx, ridx - 1))
        idx_stack.append((ridx + 1, _ridx))


def _check(items, fn):
    _items = sorted(items[:])

    fn(items)

    assert _items == items


class Node:

    def __init__(self, val: int, next: 'Node' = None):
        self.val = val
        self.next = next

    def __or__(self, next: 'Node'):
        self.next = next
        return self.next


def qsort_linked(head: Node) -> Node:

    def sort(head: Node, end: Node):
        if head is end or head.next is end:
            return head
        sentinel = Node(-1)
        sentinel.next = head
        p = head
        prev, cur = head, head.next
        while cur is not end:
            if cur.val < p.val:
                prev.next = cur.next
                cur.next = sentinel.next
                sentinel.next = cur
                cur = prev.next
            else:
                prev = cur
                cur = cur.next
        sort(sentinel.next, p)
        sort(p.next, end)

        return sentinel.next

    return sort(head, None)


def _check_linked(head):
    sorted_head = qsort_linked(head)
    prev, cur = None, sorted_head
    while cur is not None:
        if prev is not None:
            assert cur.val >= prev.val
        cur = cur.next


if __name__ == '__main__':
    for fn in (
        qsort_recursive,
        qsort_iterative,
    ):
        _check([1, 2, 3], fn)
        _check([], fn)
        _check([1, 3], fn)
        _check([3, 1], fn)
        _check([1, 1, 2, 1], fn)

    _check_linked(
        Node(1)
    )
    head = Node(2)
    head | Node(1)
    _check_linked(head)

    head = Node(1)
    head | Node(2)
    _check_linked(head)

    head = Node(1)
    head | Node(2) | Node(4) | Node(3)
    _check_linked(head)
