#!/usr/bin/env python

import sys
import random


def generate(limit, randomize=random.random):
    return [randomize() for i in xrange(limit)]


def print_sample(sample):
    s = ' '.join([str(i) for i in sample])
    print s


def main():
    if len(sys.argv) < 2:
        print 'python %s count' % sys.argv[0]
    else:
        sample = generate(int(sys.argv[1]))
        print len(sample)
        sample.sort()
        sample.reverse()
        print_sample(sample)
        sample.reverse()
       # sample.sort()
        print_sample(sample)


if __name__ == '__main__':
    main()
