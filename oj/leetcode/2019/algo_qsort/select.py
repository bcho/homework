from typing import List


class NotFoundError(Exception):
    pass


def qfind(items: List[int], k: int) -> int:
    if k >= len(items):
        raise NotFoundError

    def partition(lidx, ridx):
        if lidx >= ridx:
            if ridx == k:
                return items[ridx]

            # NOTE: should not happen
            raise NotFoundError

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

        if ridx == k:
            # found the value
            return items[ridx]
        if ridx < k:
            # sorted index is left to the target index,
            # so find at the right
            return partition(ridx + 1, _ridx)
        if ridx > k:
            # sorted index is right to the target index,
            # so find at the left
            return partition(_lidx, ridx - 1)

    return partition(0, len(items) - 1)


if __name__ == '__main__':
    assert qfind([1, 2, 3], 1) == 2
    assert qfind([1, 2, 3], 0) == 1
    assert qfind([1, 2, 3], 2) == 3
    assert qfind([3, 2, 1], 2) == 3
    assert qfind([3, 2, 1], 1) == 2
    assert qfind([3, 2, 1], 0) == 1
    assert qfind([1, 1, 1], 0) == 1
    assert qfind([1, 1, 1], 1) == 1
    assert qfind([1, 1, 1], 2) == 1
    assert qfind([1, 1, 2], 2) == 2
