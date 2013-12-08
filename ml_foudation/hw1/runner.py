#coding: utf-8


def from_dat(path):
    line_cleaner = lambda line: list(map(float, filter(None, line.split())))
    with open(path, 'r') as f:
        lines = f.readlines()
        return [line_cleaner(line) for line in lines]


def naive_pla(points):
    from pla import pla

    return pla(points)


if __name__ == '__main__':
    import sys

    if len(sys.argv) < 2:
        print('please specific input data')
        exit(1)

    points = from_dat(sys.argv[-1])

    # q15
    ret = naive_pla(points[0:10])
    print(ret)
