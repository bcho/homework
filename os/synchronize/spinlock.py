# coding: utf-8

'''
    spinlock.py
    ~~~~~~~~~~~

    Demonstration of spin lock (unusable, see descriptions below).
'''


class SpinLock(object):

    UNLOCKED = 0
    LOCKED = 1

    def __init__(self):
        self._lock = self.UNLOCKED

    def _compare_and_set(self, current_value, new_value):
        '''Perform compare-and-set.

        This should be an atomic operation
        to make sure the locking opertions won't be preempted or reorded.

        So this demo won't work in real time.
        '''
        held_value = self._lock
        if self._lock == current_value:
            self._lock = new_value
        return held_value

    def try_acquire(self):
        '''Try to acquire a lock.

        Returns True if the lock is accquired, otherwise, returns False.
        '''
        if self._compare_and_set(self.UNLOCKED, self.LOCKED) != self.UNLOCKED:
            return False
        # TODO set lock owner.
        return True

    def acquire(self):
        '''Acquire a lock.

        If the lock is holding by others, it will busy wait for the lock.
        '''
        while not self.try_acquire():
            pass  # spinning

    def release(self):
        '''Release a lock.'''
        if self._lock != self.LOCKED:
            raise RuntimeError('Release a unlocked lock.')
        # TODO should check lock owner.
        self._lock = self.UNLOCKED


if __name__ == '__main__':
    import threading
    import time

    lock = SpinLock()

    def worker(name):
        printed = False
        while not lock.try_acquire():
            if not printed:
                print('{}: lock is holding by someone else.'.format(name))
                printed = True
        print('{}: lock acquired'.format(name))

        # Do some meaningful job.
        time.sleep(2)

        # If you comment out this line, you will see the CPU hit 100%.
        lock.release()

    for i in range(5):
        threading.Thread(target=worker, args=(i, )).start()
