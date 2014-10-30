# coding: utf-8

'''
    condition_variables.py
    ~~~~~~~~~~~~~~~~~~~~~~

    Demonstration of condition variables.
'''

from time import sleep, time
from threading import Lock


# Come after: https://hg.python.org/cpython/file/2.7/Lib/threading.py#l255
class Cond(object):

    def __init__(self):
        # This lock is used to protect cond itself.
        self.lock = Lock()
        self.acquire = self.lock.acquire
        self.release = self.lock.release

        self.waiters = []

    @property
    def is_lock_acquired(self):
        '''If the caller had acquired the lock.'''
        if self.lock.acquire(0):
            self.lock.release()
            return False
        else:
            return True

    def wait(self, timeout=None):
        '''Wait for signal until notified or timeout.

        If the caller had not acquired the lock, raise RuntimeError.
        It will release the lock the caller had acquired and block.
        '''
        if not self.is_lock_acquired:
            raise RuntimeError('should acquire lock first')

        waiter = Lock()
        waiter.acquire()
        self.waiters.append(waiter)

        self.lock.release()

        # Waiter starts waiting.
        try:
            if timeout is None:
                # Let the waiter busy loop.
                waiter.acquire()
            else:
                endtime = time() + timeout
                delay = 0.0005
                remaining = endtime - time()
                while True:
                    # Check if the waiter has been freed.
                    gotit = waiter.acquire(0)
                    if gotit:
                        break
                    delay = min(delay * 2, remaining, .05)
                    sleep(delay)

                # Timeout.
                if not gotit:
                    try:
                        self.waiters.remove(waiter)
                    except ValueError:
                        pass
        finally:
            self.lock.acquire()

    def notify(self, n=1):
        '''Notify one or more waiters.

        If the caller had not acquired the lock, raise RuntimeError.
        '''
        if not self.is_lock_acquired:
            raise RuntimeError('should acquire lock first')

        for waiter in self.waiters[:n]:
            waiter.release()
            try:
                self.waiters.remove(waiter)
            except ValueError:
                pass

    def broadcast(self):
        '''Notify all waiters.

        If the caller had not acquired the lock, raise RuntimeError.
        '''
        self.notify(len(self.waiters))


if __name__ == '__main__':
    import threading
    from random import random
    from queue import Queue

    # It's better to use a queue.
    buf_q = Queue()
    cond = Cond()

    def writer(name):
        while True:
            cond.acquire()
            printed = True
            while buf_q.empty():
                if not printed:
                    print('writer {0}: waiting for job'.format(name))
                    printed = True
                cond.wait()

            item = buf_q.get(False)  # no wait
            print('writer {0}: get item: {1}'.format(name, item))

            cond.release()

    def reader(name):
        while True:
            item = '{0} from {1}'.format(str(random())[:5], name)
            cond.acquire()
            buf_q.put(item, False)  # no wait
            print('reader {0}: generating new job: {1}'.format(name, item))
            cond.broadcast()
            cond.release()
            sleep(1)

    for i in range(10):
        threading.Thread(target=writer, args=(i, )).start()
    for i in range(1):
        threading.Thread(target=reader, args=(i, )).start()
