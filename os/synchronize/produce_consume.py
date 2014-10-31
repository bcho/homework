# coding: utf-8

'''
    produce_consume.py
    ~~~~~~~~~~~~~~~~~~

    Demonstration of producer-consumer problem.
'''

import time
import random
from threading import Condition, Thread, Lock


class SizedQueue(object):

    def __init__(self, size):
        self._cap = size
        self._q_lock = Lock()
        self._q = []

    @property
    def size(self):
        self._q_lock.acquire()
        size = len(self._q)
        self._q_lock.release()

        return size

    @property
    def empty(self):
        self._q_lock.acquire()
        rv = len(self._q) == 0
        self._q_lock.release()

        return rv

    @property
    def full(self):
        self._q_lock.acquire()
        rv = len(self._q) >= self._cap
        self._q_lock.release()

        return rv

    def set_size(self, size):
        self._q_lock.acquire()
        self._cap = size
        self._q = self._q[:size]
        self._q_lock.release()

    def enqueue(self, item):
        if self.full:
            raise OverflowError('Too many items in the queue.')

        self._q_lock.acquire()
        self._q.append(item)
        self._q_lock.release()

    def pop(self):
        self._q_lock.acquire()
        rv = self._q.pop()
        self._q_lock.release()

        return rv


item_q = SizedQueue(10)
# Should put them into Queue.
has_item = Condition()
has_cell = Condition()


def make_item(name):
    return '{0} from {1}'.format(str(random.random())[:5], name)


def producer(name):
    while True:
        item = make_item(name)

        while item_q.full:
            with has_cell:
                print('producer {0}: waiting cell to put item'.format(name))
                has_cell.wait()

        if not item_q.full:
            print('producer {0}: putting item'.format(name))
            item_q.enqueue(item)

            if not item_q.empty:
                with has_item:
                    has_item.notify()

        time.sleep(0.01)


def consumer(name):
    while True:
        while item_q.empty:
            with has_item:
                print('consumer {0}: waiting item'.format(name))
                has_item.wait()

        item = item_q.pop()
        print('consumer {0}: consuming item: {1}'.format(name, item))

        if not item_q.full:
            with has_cell:
                has_cell.notify()

        time.sleep(0.02)


if __name__ == '__main__':
    producers, consumers = [], []

    item_q.set_size(10)

    for i in range(5):
        t = Thread(target=producer, args=(i, ))
        t.daemon = True
        producers.append(t)

    for i in range(20):
        t = Thread(target=consumer, args=(i, ))
        t.daemon = True
        consumers.append(t)

    [c.start() for c in producers]
    [c.start() for c in consumers]
    [c.join() for c in producers]
    [c.join() for c in consumers]
