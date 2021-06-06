class Solution:

    def countHomogenous(self, s: str) -> int:
        if len(s) < 1:
            return 0

        modulo = 10 ** 9 + 7
        rv = 0

        def add(substring_size: int):
            nonlocal rv
            times = (1 + substring_size) * substring_size // 2
            rv += times % modulo

        last_character = s[0]
        homo_substring_size = 1
        for idx in range(1, len(s)):
            c = s[idx]
            if c == last_character:
                homo_substring_size += 1
            else:
                add(homo_substring_size)
                last_character = c
                homo_substring_size = 1

        add(homo_substring_size)

        return rv % modulo


if __name__ == '__main__':
    s = Solution()

    assert s.countHomogenous('abbcccaa') == 13
    assert s.countHomogenous('a') == 1
    assert s.countHomogenous('ab') == 2
    assert s.countHomogenous('zzzzz') == 15
    print(s.countHomogenous('a' * 10 ** 5))
