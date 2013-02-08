# Name:
# Login:
# TA:
# Section:
# Q1.

def smooth(f, dx):
    """Returns the smoothed version of f, g where

    g(x) = (f(x - dx) + f(x) + f(x + dx)) / 3

    >>> square = lambda x: x ** 2
    >>> round(smooth(square, 1)(0), 3)
    0.667
    """
    "*** YOUR CODE HERE ***"
    return lambda x: (f(x - dx) + f(x) + f(x + dx)) / 3


def n_fold_smooth(f, dx, n):
    """Returns the n-fold smoothed version of f

    >>> square = lambda x: x ** 2
    >>> round(n_fold_smooth(square, 1, 3)(0), 3)
    2.0
    """
    "*** YOUR CODE HERE ***"
    def fold(f, dx, times):
        if times == n:
            return smooth(f, dx)
        else:
            return fold(smooth(f, dx), dx, times + 1)
    return fold(f, dx, 1)

# Q2.

def iterative_continued_frac(n_term, d_term, k):
    """Returns the k-term continued fraction with numerators defined by n_term
    and denominators defined by d_term.

    >>> # golden ratio
    ... round(iterative_continued_frac(lambda x: 1, lambda x: 1, 8), 3)
    0.618
    >>> # 1 / (1 + (2 / (2 + (3 / (3 + (4 / 4))))))
    ... round(iterative_continued_frac(lambda x: x, lambda x: x, 4), 6)
    0.578947
    """
    "*** YOUR CODE HERE ***"
    ret = 0
    for i in range(k, 0, -1):
        ret = n_term(i) / (ret + d_term(i))
    return ret

def recursive_continued_frac(n_term, d_term, k):
    """Returns the k-term continued fraction with numerators defined by n_term
    and denominators defined by d_term.

    >>> # golden ratio
    ... round(recursive_continued_frac(lambda x: 1, lambda x: 1, 8), 3)
    0.618
    >>> # 1 / (1 + (2 / (2 + (3 / (3 + (4 / 4))))))
    ... round(recursive_continued_frac(lambda x: x, lambda x: x, 4), 6)
    0.578947
    """
    "*** YOUR CODE HERE ***"
    def wrapper(n_term, d_term, ret, times):
        if times == 0:
            return ret
        return wrapper(n_term, d_term,
                       n_term(times) / (ret + d_term(times)), times - 1)
    return wrapper(n_term, d_term, 0, k)


# Q3.

def g(n):
    """Return the value of G(n), computed recursively.

    >>> g(1)
    1
    >>> g(2)
    2
    >>> g(3)
    3
    >>> g(4)
    10
    >>> g(5)
    22
    """
    "*** YOUR CODE HERE ***"
    if n <= 3:
        return n
    return g(n - 1) + 2 * g(n - 2) + 3 * g(n - 3)


def g_iter(n):
    """Return the value of G(n), computed iteratively.
    >>> g_iter(1)
    1
    >>> g_iter(2)
    2
    >>> g_iter(3)
    3
    >>> g_iter(4)
    10
    >>> g_iter(5)
    22
    >>> g_iter(6) == g(6)
    True
    """
    "*** YOUR CODE HERE ***"
    if n <= 3:
        return n
    g1, g2, g3 = 1, 2, 3
    for i in range(4, n + 1):
        g1, g2, g3 = g2, g3, g1 * 3 + g2 * 2 + g3
    return g3


# Q4.

from operator import sub, mul

def make_anonymous_factorial():
    """Return the value of an expression that computes factorial.

    >>> make_anonymous_factorial()(5)
    120
    """
    return lambda x: 1 if x <= 1 else mul(x,
            make_anonymous_factorial()(sub(x, 1)))
