from typing import List


class Solution:
    def findLadders(
        self,
        beginWord: str,
        endWord: str,
        wordList: List[str]
    ) -> List[List[str]]:
        from collections import deque

        DEBUG = False

        _diff_count = {}

        def diff_count(a, b):
            if a > b:
                return diff_count(b, a)
            if a == b:
                return False
            if (a, b) in _diff_count:
                return _diff_count[(a, b)]

            count = 0
            for ac, bc in zip(a, b):
                if ac == bc:
                    continue
                count += 1
            _diff_count[(a, b)] = count
            return _diff_count[(a, b)]

        def can_convert_to(a, b):
            return diff_count(a, b) == 1

        # find the shortest path from beginWord to endWord
        def find_shortest_length():
            inqueue_idxs = set()
            to_visit = deque([
                (idx, 1)
                for idx, word in enumerate(wordList)
                if can_convert_to(beginWord, word)
            ])
            while len(to_visit) > 0:
                if DEBUG:
                    print(f'before visit: {to_visit}')

                idx, length = to_visit.popleft()
                visiting_word = wordList[idx]
                if DEBUG:
                    print(f'visiting: {wordList[idx]}')
                if wordList[idx] == endWord:
                    if DEBUG:
                        print(length)
                    return length
                for target_idx, target_word in enumerate(wordList):
                    if target_idx in inqueue_idxs:
                        continue
                    if not can_convert_to(target_word, visiting_word):
                        continue
                    inqueue_idxs.add(target_idx)
                    to_visit.append((target_idx, length + 1))

            if DEBUG:
                print('no path')

            return float('inf')

        def load_shortest_paths(shortest_length: int):
            paths = []

            def dfs(visited_idxs, path_idxs, visiting_idx):
                if wordList[visiting_idx] == endWord:
                    paths.append([beginWord] + [
                        wordList[i]
                        for i in path_idxs + [visiting_idx]
                    ])
                    return
                visiting_word = wordList[visiting_idx]
                diff_count_to_target = diff_count(endWord, visiting_word)
                if diff_count_to_target + len(path_idxs) >= shortest_length:
                    return
                visited_idxs.add(visiting_idx)
                for target_idx, target_word in enumerate(wordList):
                    if target_idx in visited_idxs:
                        continue
                    if not can_convert_to(target_word, visiting_word):
                        continue
                    dfs(visited_idxs, path_idxs + [visiting_idx], target_idx)
                visited_idxs.remove(visiting_idx)

            for idx, word in enumerate(wordList):
                if not can_convert_to(beginWord, word):
                    continue
                dfs(set(), [], idx)

            return paths

        shortest_length = find_shortest_length()
        if shortest_length > len(wordList):
            # unable to convert
            return []

        rv = load_shortest_paths(shortest_length)
        if DEBUG:
            for path in rv:
                print('->'.join(path))
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
