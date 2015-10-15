import sys
import random


def generate_matrix(name, a, b):
    for i in range(a):
        for j in range(b):
            print('{},{},{},{}'.format(name, i, j, random.randint(1, 5)))


assert len(sys.argv) == 4
m, n, p = [int(i) for i in sys.argv[1:4]]

print(','.join(sys.argv[1:4]))
generate_matrix('A', m, n)
generate_matrix('B', n, p)
