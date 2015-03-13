def qsort(a):
    if not a:
        return []
    pivot, a = a[0], a[1:]
    smaller, bigger = [i for i in a if i <= pivot], [i for i in a if i > pivot]
    return qsort(smaller) + [pivot] + qsort(bigger)
