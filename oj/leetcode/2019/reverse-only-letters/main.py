class Solution:
    def reverseOnlyLetters(self, S: str) -> str:
        def is_letter(s: str) -> bool:
            ords = ord(s)
            return 97 <= ords <= 122 or 65 <= ords <= 90

        chars = [c for c in S]

        lidx, ridx = 0, len(chars) - 1
        while lidx < ridx:
            while not is_letter(chars[lidx]) and lidx < ridx:
                lidx += 1
            while not is_letter(chars[ridx]) and lidx < ridx:
                ridx -= 1

            if lidx < ridx:
                chars[lidx], chars[ridx] = chars[ridx], chars[lidx]
                lidx += 1
                ridx -= 1

        return ''.join(chars)


if __name__ == '__main__':
    s = Solution()
    assert s.reverseOnlyLetters('') == ''
    assert s.reverseOnlyLetters('a') == 'a'
    assert s.reverseOnlyLetters('ab') == 'ba'
    assert s.reverseOnlyLetters('abc') == 'cba'
    assert s.reverseOnlyLetters('-') == '-'
    assert s.reverseOnlyLetters('-!') == '-!'
    assert s.reverseOnlyLetters('ab-cd') == 'dc-ba'
    assert s.reverseOnlyLetters('a-bC-dEf-ghIj') == 'j-Ih-gfE-dCba'
    assert s.reverseOnlyLetters(
        'Test1ng-Leet=code-Q!'
    ) == 'Qedo1ct-eeLg=ntse-T!'
