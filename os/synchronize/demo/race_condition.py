# coding: utf-8

from threading import Thread


global_val = 0


def update_global_val():
    global global_val

    for i in xrange(10000):
        global_val = global_val + 1


threads = []

for i in range(10):
    t = Thread(target=update_global_val)
    t.daemon = True
    t.start()

    threads.append(t)


for t in threads:
    t.join()


print global_val
assert global_val == 100000
