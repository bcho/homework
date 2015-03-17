NOT_EXIST = -1


def bsearch(haystack, needle):
    def s(l, r):
        if l > r:
            return NOT_EXIST
        mid = (l + r) / 2
        if haystack[mid] == needle:
            while mid >= 1 and haystack[mid - 1] == needle:
                mid = mid - 1
            return mid
        elif haystack[mid] < needle:
            return s(mid + 1, r)
        elif haystack[mid] > needle:
            return s(l, mid - 1)

    return s(0, len(haystack) - 1)
