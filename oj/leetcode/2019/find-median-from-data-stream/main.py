class MedianFinder:

    class Heap:

        def __init__(self, cmp):
            self.cmp = cmp
            self.items = []

        @property
        def size(self):
            return len(self.items)

        def _parent_idx(self, idx):
            return (idx - 1) // 2

        def _left_child_idx(self, idx):
            return idx * 2 + 1

        def _right_child_idx(self, idx):
            return idx * 2 + 2

        def _swap(self, a, b):
            self.items[a], self.items[b] = self.items[b], self.items[a]

        @property
        def peak(self):
            assert len(self.items) > 0
            return self.items[0]

        def add(self, value):
            self.items.append(value)

            # adjust the heap
            child_idx = len(self.items) - 1
            while child_idx > 0:
                parent_idx = self._parent_idx(child_idx)
                if self.cmp(self.items[parent_idx], self.items[child_idx]):
                    # already match
                    break
                self._swap(parent_idx, child_idx)
                child_idx = parent_idx

        def remove(self):
            assert len(self.items) > 0
            rv = self.items[0]
            if len(self.items) == 1:
                self.items = []
            else:
                # sink to adjust the heap
                self.items[0] = self.items.pop()
                parent_idx = 0
                while True:
                    left_child_idx = self._left_child_idx(parent_idx)
                    if left_child_idx >= len(self.items):
                        # reached leave
                        break
                    child_idx = left_child_idx
                    child_value = self.items[left_child_idx]
                    right_child_idx = self._right_child_idx(parent_idx)
                    if right_child_idx < len(self.items):
                        if self.cmp(
                            self.items[right_child_idx],
                            child_value,
                        ):
                            child_idx = right_child_idx
                            child_value = self.items[right_child_idx]
                    if self.cmp(self.items[parent_idx], child_value):
                        # adjust finished
                        break
                    self._swap(parent_idx, child_idx)
                    parent_idx = child_idx

            return rv

    def __init__(self):
        """
        initialize your data structure here.
        """
        self.left_part = MedianFinder.Heap(lambda a, b: a > b)
        self.right_part = MedianFinder.Heap(lambda a, b: a < b)

    def addNum(self, num: int) -> None:
        if self.right_part.size == 0:
            # fast path: no value recorded, add to right
            self.right_part.add(num)
        elif num > self.right_part.peak:
            # this value is larger than the smaller value in the right half,
            # add to right half
            self.right_part.add(num)
        else:
            # this value is smaller than the smaller value in the left half,
            # add to left half
            self.left_part.add(num)

        # median invariant:
        #
        # odd size: left_part + 1 <= right_part
        # even size: left_part = right_part
        if self.right_part.size > self.left_part.size + 1:
            # unbalanced, pop to the left
            self.left_part.add(self.right_part.remove())
        elif self.left_part.size > self.right_part.size:
            # unbalanced, pop to the left
            self.right_part.add(self.left_part.remove())

    def findMedian(self) -> float:
        if self.right_part.size < 1:
            # empty
            return 0

        if self.left_part.size == self.right_part.size:
            return (self.left_part.peak + self.right_part.peak) / 2
        return self.right_part.peak


if __name__ == '__main__':
    f = MedianFinder()
    f.addNum(-1)
    assert f.findMedian() == -1
    f.addNum(-2)
    assert f.findMedian() == -1.5
    f.addNum(-3)
    assert f.findMedian() == -2
    f.addNum(-4)
    assert f.findMedian() == -2.5
    f.addNum(-5)
    assert f.findMedian() == -3
