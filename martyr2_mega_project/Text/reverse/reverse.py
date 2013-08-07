#coding: utf-8

import sys


def reverse(nstr, rstr):
    if not nstr:
        return rstr
    return reverse(nstr[1:], nstr[0] + rstr)


def main():
    print reverse(sys.stdin.read(), '').strip()


if __name__ == '__main__':
    main()
