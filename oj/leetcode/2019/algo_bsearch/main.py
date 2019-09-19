from typing import List


def binary_search(items: List[int], t: int) -> int:
    if len(items) < 1:
        return -1

    # ridx is the last index that no match the target
    lidx, ridx = 0, len(items)
    while lidx < ridx:
        midx = (lidx + ridx) // 2
        if items[midx] < t:
            lidx = midx + 1
        elif items[midx] > t:
            ridx = midx
        else:
            return midx

    return -1


def binary_search_leftmost(items: List[int], t: int) -> int:
    if len(items) < 1:
        return 0

    lidx, ridx = 0, len(items)
    while lidx < ridx:
        midx = (lidx + ridx) // 2
        if items[midx] < t:
            lidx = midx + 1
        else:
            # items[midx] >= t
            # shrink the window toward the left
            ridx = midx

    # leftmost index that break the loop
    return lidx


def binary_search_rightmost(items: List[int], t: int) -> int:
    if len(items) < 1:
        return 0

    lidx, ridx = 0, len(items)
    while lidx < ridx:
        midx = (lidx + ridx) // 2
        if items[midx] > t:
            ridx = midx
        else:
            # items[midx] <= t
            # shrink the window toward the right
            lidx = midx + 1

    # rightmost index that break the loop
    return lidx - 1


if __name__ == '__main__':
    assert binary_search([1, 2, 3], 2) == 1
    assert binary_search([], 2) == -1
    assert binary_search([1, 2, 3], 4) == -1
    assert binary_search([1, 2, 3], 1) == 0
    assert binary_search([1, 2, 3], 3) == 2
    assert binary_search([1, 2, 2, 3], 3) == 3
    assert binary_search([1, 2, 2, 3], 2) == 2
    assert binary_search([1, 2, 2, 2, 3], 2) in (1, 2, 3)

    assert binary_search_leftmost([1, 2, 2, 2, 3], 2) == 1
    assert binary_search_leftmost([2, 2, 2, 2, 3], 2) == 0
    assert binary_search_leftmost([2, 2, 2, 2, 3], 3) == 4
    assert binary_search_leftmost([1, 1, 2, 3], 2) == 2
    assert binary_search_leftmost([1, 1, 2, 3], 4) == 4
    assert binary_search_leftmost([1, 1, 2, 3], 10) == 4
    assert binary_search_leftmost([1, 1, 3, 3], 2) == 2

    assert binary_search_rightmost([1, 2, 2, 2, 3], 1) == 0
    assert binary_search_rightmost([1, 2, 2, 2, 3], 3) == 4
    assert binary_search_rightmost([1, 2, 2, 2, 3], 2) == 3
    assert binary_search_rightmost([1, 2, 2, 2, 3], 4) == 4
    assert binary_search_rightmost([1, 2, 2, 2, 3], 10) == 4
