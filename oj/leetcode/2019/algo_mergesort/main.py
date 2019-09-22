def merge_sort(items):

    def sort(a):
        if len(a) < 1:
            return a
        if len(a) == 1:
            return a

        midx = len(a) // 2
        left_part_sorted = sort(a[:midx])
        right_part_sorted = sort(a[midx:])
        merged = []
        while True:
            if len(left_part_sorted) < 1:
                break
            if len(right_part_sorted) < 1:
                break
            if left_part_sorted[0] <= right_part_sorted[0]:
                merged.append(left_part_sorted[0])
                left_part_sorted = left_part_sorted[1:]
            else:
                merged.append(right_part_sorted[0])
                right_part_sorted = right_part_sorted[1:]
        while len(left_part_sorted) > 0:
            merged.append(left_part_sorted[0])
            left_part_sorted = left_part_sorted[1:]
        while len(right_part_sorted) > 0:
            merged.append(right_part_sorted[0])
            right_part_sorted = right_part_sorted[1:]

        return merged

    return sort(items)


def check(arr, fn):
    expected = sorted(arr)
    assert expected == fn(arr)


if __name__ == '__main__':
    check([4], merge_sort)
    check([], merge_sort)
    check([1, 2, 3, 4, 5], merge_sort)
    check([5, 3, 3, 1, 2], merge_sort)
