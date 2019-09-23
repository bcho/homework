from typing import List


class Solution:
    def findLadders(
        self,
        beginWord: str,
        endWord: str,
        wordList: List[str]
    ) -> List[List[str]]:
        from collections import deque

        def can_convert(a, b):
            diff_count = 0
            for ac, bc in zip(a, b):
                if ac != bc:
                    diff_count += 1
                if diff_count > 1:
                    return False
            return diff_count == 1

        word_list_set = set(wordList)

        found, min_size = False, -1
        rv = []
        pending = deque([
            (word, [beginWord])
            for word in wordList
            if can_convert(word, beginWord)
        ])
        visited_words = set()
        while len(pending) > 0:
            word, paths = pending.popleft()
            visited_words.add(word)
            if found and len(paths) >= min_size:
                continue
            if word == endWord:
                # found
                paths = paths + [endWord]
                rv.append(paths)
                found, min_size = True, len(paths)
                continue

            for idx in range(len(word)):
                for ch in range(27):
                    c = chr(ch + 97)
                    if c == word[idx]:
                        continue
                    new_word = word[:idx] + c + word[idx+1:]
                    if new_word not in word_list_set:
                        continue
                    if new_word in visited_words:
                        continue
                    pending.append((new_word, paths + [word]))

        return rv


if __name__ == '__main__':
    s = Solution()
    assert s.findLadders(
        'hit', 'cog', ['hot', 'dot', 'dog', 'lot', 'log', 'cog']
    ) == [
        ['hit', 'hot', 'dot', 'dog', 'cog'],
        ['hit', 'hot', 'lot', 'log', 'cog'],
    ]

    assert s.findLadders(
        'hit', 'cog', ['hot', 'dot', 'dog', 'lot', 'log']
    ) == []
