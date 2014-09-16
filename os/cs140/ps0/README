This package contains cs140 ps0 starter code. The included Makefile
will compile your solutions to the caltrain and reaction synchronisation
problems. The resulting binaries will try to stress-test what you
wrote and should hopefully help you to shake out any bugs.

You'll need to fill in caltrain.c and reaction.c appropriately to
complete this assignment (the tests will certainly fail before you do
so). These two files, and only these two files, should be submitted for
grading. See the website for forthcoming submission details.

You are to use the Pintos lock and condition variable APIs. The following
types are defined already for your use:
    struct lock
    struct condition
As are the following functions:
    void lock_init(struct lock *lock);
    void lock_acquire(struct lock *lock);
    void lock_release(struct lock *lock);
    void cond_init(struct condition *cond);
    void cond_wait(struct condition *cond, struct lock *lock);
    void cond_signal(struct condition *cond, struct lock *lock);
    void cond_broadcast(struct condition *cond, struct lock *lock);
See the Pintos documentation for more information on these synchronisation
primitives.

No other files should need to be modified. Compile using 'make'. To
run a bunch of tests, you can try 'make run'. These programs have been
tested on the myth linux cluster and OS X and should be pretty portable to
other UNIX-like OSes.

The tests have a lot of randomness built in and aren't flawless (their
passing doesn't guarantee a perfect implementation). You may want to
run many times to get better assurance of your solution's sanity. You're
welcome to extend the tests any way you see fit, but they won't be
submitted. You should refrain from using any other libraries or functions
in your solutions. We should be able to untar this distribution, copy over
your caltrain.c and reaction.c files, and compile and run the original
tests.

Note that hard timeouts are used to catch some issues like deadlock.
It's possible that on busy shared machines (or perhaps really anemic
netbooks) they're too conservative. If you're dead sure your code is
correct and tests still don't pass, just come by office hours and
we'll try to help you figure out what's going wrong.
