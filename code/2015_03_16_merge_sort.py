def merge_sort(a):

    # Merge
    def m(l, r):
        a = []
        while l and r:
            if l[0] < r[0]:
                a.append(l.pop(0))
            else:
                a.append(r.pop(0))
        return a + l + r

    # Sort
    def s(a):
        if not a or len(a) < 2:
            return a or []
        return m(s(a[:len(a) / 2]), s(a[len(a) / 2:]))

    return s(a)
