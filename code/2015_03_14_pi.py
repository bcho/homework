def pi(n):
    '''Calculate pi with Gregory-Leibniz formula, happy PI day!'''
    return 4 * sum(map(lambda k: (-1) ** (k + 1) / (2.0 * k - 1), range(1, n)))
