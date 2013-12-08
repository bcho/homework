#coding: utf-8


def g(a, b):
    def sign(e):
        if e == 0:
            return -1
        return e / abs(e)
    return sign(a * b)


def is_sign(y, sign):
    return filter(lambda x: x != sign, y) == []


def cal(x, w):
    return map(g, x, w)


def generate_w(points):
    return [0] * len(points[0][:-1])


def find_mistake(points, w):
    for point in points:
        xs = point[:-1]
        if not is_sign(cal(xs, w), point[-1]):
            return point


def correct_mistake(mistake, ws):
    xs, sign = mistake[:-1], mistake[-1]
    iterations = 0
    while True:
        ys = cal(xs, ws)
        if is_sign(ys, sign):
            break
        next_ws = []
        for xi, yi, wi in zip(xs, ys, ws):
            if yi != sign:
                wi = wi + sign * xi
            next_ws.append(wi)
        iterations = iterations + 1
        ws = next_ws
    return ws, iterations


def pla(points):
    w = generate_w(points)
    iterations = 0
    while True:
        mistake = find_mistake(points, w)
        if not mistake:
            break
        w, i = correct_mistake(mistake, w)
        iterations = iterations + i

    return w, iterations
