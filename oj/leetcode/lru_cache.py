class Item(object):

    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.prev = None
        self.next = None

    def set_next(self, next_item):
        self.next = next_item
        self.next.prev = self

    def set_prev(self, prev_item):
        self.prev = prev_item
        self.prev.next = self


class LRUCache(object):

    MISSING_ITEM = -1

    def __init__(self, capacity):
        self._cap = capacity
        self._cells = {}

        self._cells_head = Item(None, None)
        self._cells_tail = Item(None, None)
        self._cells_head.set_next(self._cells_tail)

    def get(self, key):
        item = self._cells.get(key)
        if item is None:
            return self.MISSING_ITEM

        # Move this item to head.
        prev_item, next_item = item.prev, item.next
        prev_item.set_next(next_item)
        item.set_next(self._cells_head.next)
        item.set_prev(self._cells_head)

        return item.value

    def set(self, key, value):
        # Key already exists.
        item_value = self.get(key)
        if item_value != self.MISSING_ITEM:
            self._cells[key].value = value
            return

        # Check size.
        if len(self._cells) >= self._cap:
            self.free_cell()

        # Create a new item,
        item = Item(key, value)
        self._cells[key] = item

        # .. and put it to head.
        prev_item, next_item = self._cells_head, self._cells_head.next
        item.set_next(next_item)
        item.set_prev(prev_item)

    def free_cell(self):
        least_use_item = self._cells_tail.prev
        # Should free on empty list.
        if least_use_item is self._cells_head:
            return

        last_but_two_item = least_use_item.prev
        last_but_two_item.set_next(self._cells_tail)

        del self._cells[least_use_item.key]
        del least_use_item


if __name__ == '__main__':
    cache = LRUCache(1)

    cache.set(2, 1)
    assert cache.get(2) == 1

    cache.set(3, 2)
    assert cache.get(2) == -1
    assert cache.get(3) == 2
