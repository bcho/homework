# coding: utf-8

from threading import Thread, Lock


mutex1 = Lock()
mutex2 = Lock()


def t(la, lb, la_name, lb_name):
    with la:
        # Ensure two thread start in same time.
        for i in range(1000000):
            pass
        print('do something with ' + la_name)
        print('try to acquire ' + lb_name)
        with lb:
            print('do something with ' + lb_name)


p1 = Thread(target=t, args=(mutex1, mutex2, 'mutex1', 'mutex2'))
p1.start()
p2 = Thread(target=t, args=(mutex2, mutex1, 'mutex2', 'mutex1'))
p2.start()

p1.join()
p2.join()
