class Solution:

    def lognestCommonPrefix(self, strs):

        def find_length(strs):
            if not strs:
                return 0

            length = 0
            cur_char = None

            datum = strs.pop()
            while True:
                if length >= len(datum):
                    return length

                cur_char = datum[length]
                for string in strs:
                    if length >= len(string):
                        return length

                    if string[length] != cur_char:
                        return length

                length = length + 1

        if not strs:
            return ''

        return strs[0][:find_length(strs)]


if __name__ == '__main__':
    s = Solution()

    print(s.lognestCommonPrefix(['abcd', 'abcd', '']))
