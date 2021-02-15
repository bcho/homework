class Solution:
    def maximumTime(self, time: str) -> str:
        rv = list(time)
        h0, h1, m0, m1 = time[0], time[1], time[3], time[4]
        if h0 == '?' and h1 == '?':
            rv[0], rv[1] = '2', '3'
        elif h0 == '?' and h1 >= '4':
            rv[0] = '1'
        elif h0 == '?' and h1 < '4':
            rv[0] = '2'
        elif h0 == '2' and h1 == '?':
            rv[1] = '3'
        elif h0 != '2' and h1 == '?':
            rv[1] = '9'
        if m0 == '?':
            rv[3] = '5'
        if m1 == '?':
            rv[4] = '9'

        return ''.join(rv)


if __name__ == '__main__':
    s = Solution()
    assert s.maximumTime('?4:03') == '14:03'
    assert s.maximumTime('2?:?0') == '23:50'
    assert s.maximumTime('0?:3?') == '09:39'
    assert s.maximumTime('1?:22') == '19:22'
    assert s.maximumTime('??:22') == '23:22'
    assert s.maximumTime('?5:13') == '15:13'