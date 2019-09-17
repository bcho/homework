from typing import List


class Solution:

    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        from collections import defaultdict

        # base cases
        if len(s) < 1:
            return []
        if len(words) < 1:
            return []

        rv = []

        word_counts = defaultdict(int)
        for word in words:
            # count all words
            word_counts[word] += 1

        word_size = len(words[0])
        window_size = len(words) * word_size
        shift_window_idx = 0
        # O(n * k), where n = size of the string, k = count of the words
        while shift_window_idx <= len(s) - window_size:
            word_counts_in_this_window = defaultdict(int)

            # check this window
            word_idx_range = range(
                shift_window_idx,
                window_size + shift_window_idx,
                word_size,
            )
            window_matched = True
            for word_idx in word_idx_range:
                word = s[word_idx: word_idx + word_size]
                if word not in word_counts:
                    # unexpected word, cannot build the window
                    window_matched = False
                    break
                # record the word
                word_counts_in_this_window[word] += 1
                if word_counts_in_this_window[word] > word_counts[word]:
                    # count exceeded, not a valid window
                    window_matched = False
                    break
            if window_matched:
                rv.append(shift_window_idx)

            # forward the window
            shift_window_idx += 1

        return rv


if __name__ == '__main__':
    s = Solution()
    assert s.findSubstring('barfoothefoobarman', ['foo', 'bar']) == [0, 9]
    assert s.findSubstring(
        'wordgoodgoodgoodbestword',
        ['word', 'good', 'best', 'word']
    ) == []
    assert s.findSubstring('hello', ['h', 'e', 'l', 'l', 'o']) == [0]
