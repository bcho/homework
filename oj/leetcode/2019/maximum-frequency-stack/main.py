class FreqStack:

    def __init__(self):
        from collections import defaultdict

        # maintain current max frequency
        self.max_freq = 0
        # value distributed in different frequencies
        self.freq_buckets = defaultdict(list)
        # frequencies indexed by value
        self.freq_of_value = defaultdict(int)

    def push(self, x: int) -> None:
        # update the frequencies index
        self.freq_of_value[x] += 1
        # update the max frequency
        self.max_freq = max(self.max_freq, self.freq_of_value[x])
        # push to the frequency stack
        self.freq_buckets[self.freq_of_value[x]].append(x)

    def pop(self) -> int:
        assert self.max_freq != 0
        assert len(self.freq_buckets[self.max_freq]) > 0

        # pop from largest frequency stack
        value = self.freq_buckets[self.max_freq].pop()
        # update the frequencies index
        self.freq_of_value[value] -= 1
        if self.freq_of_value[value] == 0:
            self.freq_of_value.pop(value)

        # update the max frequency
        while len(self.freq_buckets[self.max_freq]) < 1 and self.max_freq > 0:
            self.freq_buckets.pop(self.max_freq)
            self.max_freq -= 1

        return value


if __name__ == '__main__':
    f = FreqStack()
    for v in [5, 7, 5, 7, 4, 5]:
        f.push(v)
    assert f.pop() == 5
    assert f.pop() == 7
    assert f.pop() == 5
    assert f.pop() == 4
