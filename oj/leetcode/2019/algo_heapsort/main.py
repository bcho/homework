from typing import List


def heap_sort(items: List[int]):

    def parent_idx(idx):
        return (idx - 1) // 2

    def left_child_idx(idx):
        return 2 * idx + 1

    def right_child_idx(idx):
        return 2 * idx + 2

    def swap(a, b):
        items[a], items[b] = items[b], items[a]

    def sink(start_idx, end_idx):
        parent_idx = start_idx
        while True:
            if parent_idx > end_idx:
                # reach the end of the tree
                break
            child_idx = left_child_idx(parent_idx)
            if child_idx > end_idx:
                # no child, reach the end
                break

            # find max child
            max_child = items[child_idx]
            rchild_idx = right_child_idx(parent_idx)
            if rchild_idx <= end_idx and items[rchild_idx] > max_child:
                child_idx = rchild_idx
                max_child = items[rchild_idx]

            # check if current heap invariant holds
            if items[parent_idx] < max_child:
                swap(parent_idx, child_idx)
                # sub tree updated, sink children
                parent_idx = child_idx
                continue

            # sink finished
            break

    # flow:
    #
    # 1. build a heap with the *maximum* value at the root(top)
    # 2. move the maximum to the end, mark as sorted
    # 3. update the heap from top, restore the heap order (repeat n times)

    # step 1 (O(n))
    # build the heap, move the largest value to the top
    for idx in range(len(items) - 1, -1, -1):
        sink(idx, len(items) - 1)

    # step 2 (O(n))
    for idx in range(len(items) - 1, -1, -1):
        # move the largest value to the last (sorted)
        swap(0, idx)
        # step 3 (O(logn))
        # rebuild the heap from top
        sink(0, idx - 1)


def _check(items, fn):
    _items = sorted(items[:])

    fn(items)

    assert _items == items


if __name__ == '__main__':
    _check([5, 3, 1, 2, 4], heap_sort)
    _check([1, 2, 3, 4, 5], heap_sort)
    _check([5, 4, 3, 2, 1], heap_sort)
    _check([1, 1, 1, 1, 1], heap_sort)
    _check([1, 1, 2, 1, 1], heap_sort)
