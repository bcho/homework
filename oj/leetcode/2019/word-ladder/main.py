from typing import List


class Solution:
    def ladderLength(
        self,
        beginWord: str,
        endWord: str,
        wordList: List[str],
    ) -> int:
        from collections import deque

        if len(wordList) < 1:
            return 0

        wordList = set(wordList)

        def can_convert(a, b):
            diff_count = 0
            for ac, bc in zip(a, b):
                if ac != bc:
                    diff_count += 1
                    if diff_count > 1:
                        return False
            return diff_count == 1

        visited_words = set()
        pending = deque([
            (word, 2)
            for word in wordList
            if can_convert(word, beginWord)
        ])
        if beginWord in wordList:
            # special case
            pending.appendleft((beginWord, 1))
        while len(pending) > 0:
            word, distance = pending.popleft()
            visited_words.add(word)
            if word == endWord:
                return distance
            for new_word in wordList:
                if new_word in visited_words:
                    continue
                if not can_convert(new_word, word):
                    continue
                if new_word == endWord:
                    return distance + 1
                pending.append((new_word, distance + 1))

        return 0
