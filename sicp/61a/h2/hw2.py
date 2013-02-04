# Name:
# Login:
# TA:
# Section:


def square(x):
    """Return x squared."""
    return x * x

# Q1.


def product(n, term):
    """Return the product of the first n terms in a sequence.

    term -- a function that takes one argument

    >>> product(4, square)
    576
    """
    "*** YOUR CODE HERE ***"
    ret = 1
    for i in range(1, n + 1, 1):
        ret *= term(i)
    return ret


def factorial(n):
    """Return n factorial by calling product.

    >>> factorial(4)
    24
    """
    "*** YOUR CODE HERE ***"
    return product(n, lambda x: x)


# Q2.

def accumulate(combiner, start, n, term):
    """Return the result of combining the first n terms in a sequence."""
    "*** YOUR CODE HERE ***"
    ret = start
    for i in range(1, n + 1, 1):
        ret = combiner(ret, term(i))
    return ret


def summation_using_accumulate(n, term):
    """An implementation of summation using accumulate.

    >>> summation_using_accumulate(4, square)
    30
    """
    "*** YOUR CODE HERE ***"
    return accumulate(lambda x, y: x + y, 0, n, term)


def product_using_accumulate(n, term):
    """An implementation of product using accumulate.

    >>> product_using_accumulate(4, square)
    576
    """
    "*** YOUR CODE HERE ***"
    return accumulate(lambda x, y: x * y, 1, n, term)


# Q3.

def double(f):
    """Return a function that applies f twice.

    f -- a function that takes one argument

    >>> double(square)(2)
    16
    """
    "*** YOUR CODE HERE ***"
    def wrapper(arg):
        return f(f(arg))
    return wrapper


# Q4.

def repeated(f, n):
    """Return the function that computes the nth application of f.

    f -- a function that takes one argument
    n -- a positive integer

    >>> repeated(square, 2)(5)
    625
    >>> repeated(square, 4)(5)
    152587890625
    """
    "*** YOUR CODE HERE ***"
    def wrapper(arg):
        return f(arg) if n == 1 else f(repeated(f, n - 1)(arg))
    return wrapper


def compose1(f, g):
    """Return a function h, such that h(x) = f(g(x))."""
    def h(x):
        return f(g(x))
    return h


# Q5.

def zero(f):
    return lambda x: x


def successor(n):
    return lambda f: lambda x: f(n(f)(x))


def one(f):
    """Church numeral 1."""
    "*** YOUR CODE HERE ***"
    return successor(zero)


def two(f):
    """Church numeral 2."""
    "*** YOUR CODE HERE ***"
    return successor(one)


'''
def church_to_int(n):
    """Convert the Church numeral n to a Python integer.

    >>> church_to_int(zero)
    0
    >>> church_to_int(one)
    1
    >>> church_to_int(two)
    2
    """
    "*** YOUR CODE HERE ***"
    return n(lambda x: x + 1)(0)  # ?

def add_church(m, n):
    """Return the Church numeral for m + n, for Church numerals m and n.

    >>> three = successor(two)
    >>> church_to_int(add_church(two, three))
    5
    """
    "*** YOUR CODE HERE ***"


def mul_church(m, n):
    """Return the Church numeral for m * n, for Church numerals m and n.

    >>> three = successor(two)
    >>> four = successor(three)
    >>> church_to_int(mul_church(two, three))
    6
    >>> church_to_int(mul_church(three, four))
    12
    """
    "*** YOUR CODE HERE ***"


def pow_church(m, n):
    """Return the Church numeral for m ** n, for Church numerals m and n.

    >>> three = successor(two)
    >>> church_to_int(pow_church(two, three))
    8
    >>> church_to_int(pow_church(three, two))
    9
    """
    "*** YOUR CODE HERE ***"
'''
