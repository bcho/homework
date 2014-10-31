# coding: utf-8

'''
    semaphore.py
    ~~~~~~~~~~~~

    Demonstration of semaphore.
'''

from threading import Lock, Condition


class Semaphore(object):

    def __init__(self, count=1):
        if count < 1:
            raise ValueError('Semaphore count should be at least 1.')
        self._count = count

        self._cond = Condition(Lock())

    def P(self):
        '''Acquire a lock.

        Block until acquired successfully.
        '''
        with self._cond:
            while self._count <= 0:
                self._cond.wait()  # block and wait for the lock.
            else:
                self._count = self._count - 1

    def V(self):
        '''Release a lock.'''
        with self._cond:
            self._count = self._count + 1
            self._cond.notify()  # wake up a waiting thread.


if __name__ == '__main__':
    import threading
    import random

    sema = Semaphore()
    threads1 = []
    threads2 = []
    counter1 = 0
    counter2 = 0

    def worker1(name, sleep_time):
        global counter1

        sema.P()
        print('worker1 {}: increasing the counter'.format(name))
        for i in range(10000):
            counter1 = counter1 + 1
        sema.V()

    def worker2(name, sleep_time):
        global counter2

        for i in range(10000):
            counter2 = counter2 + 1
        print('worker2 {}: increasing the counter'.format(name))

    print('Counter1 is {}'.format(counter1))
    print('Counter2 is {}'.format(counter2))
    for i in range(10):
        sleep_time = random.random()

        t = threading.Thread(target=worker1, args=(i, sleep_time))
        t.daemon = True
        threads1.append(t)

        t = threading.Thread(target=worker2, args=(i, sleep_time))
        t.daemon = True
        threads2.append(t)

    for i, _ in enumerate(threads1):
        threads1[i].start()
        threads2[i].start()

    for i, _ in enumerate(threads1):
        threads1[i].join()
        threads2[i].join()

    print('Counter1 is {}'.format(counter1))
    print('Counter2 is {}'.format(counter2))
