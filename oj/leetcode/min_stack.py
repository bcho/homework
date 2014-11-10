class MinStack:

    def __init__(self):
        self._items = []
        self._mins = []

    def push(self, x):
        if not self._mins or x <= self._mins[-1]:
            self._mins.append(x)
        self._items.append(x)

    def pop(self):
        item = self._items.pop()
        if self._mins and item == self._mins[-1]:
            self._mins.pop()

    def top(self):
        if self._items:
            return self._items[-1]

    def getMin(self):
        if self._mins:
            return self._mins[-1]


if __name__ == '__main__':
    s = MinStack()
    s.push(1)
    s.push(2)
    s.push(3)

    print(s.getMin())
    s.pop()
    print(s.getMin())
