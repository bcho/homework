#include "pintos_thread.h"

// Forward declaration. This function is implemented in reaction-runner.c,
// but you needn't care what it does. Just be sure it's called when
// appropriate within reaction_o()/reaction_h().
void make_water();

struct reaction {
    int h, o;
    struct lock lock;
    struct condition has_new_h, has_enough_o;
};

void
reaction_init(struct reaction *reaction)
{
    reaction->h = 0;
    reaction->o = 0;
    lock_init(&reaction->lock);
    cond_init(&reaction->has_new_h);
    cond_init(&reaction->has_enough_o);
}

void
reaction_h(struct reaction *reaction)
{
    lock_acquire(&reaction->lock);
    reaction->h += 1;

    cond_signal(&reaction->has_new_h, &reaction->lock);

    // Waiting for an O to exit. 
    cond_wait(&reaction->has_enough_o, &reaction->lock);

    lock_release(&reaction->lock);
}

void
reaction_o(struct reaction *reaction)
{
    lock_acquire(&reaction->lock);
    reaction->o += 1;

    // Wait until there are enough H.
    while (reaction->h < 2)
        cond_wait(&reaction->has_new_h, &reaction->lock);

    // Notify 2 H to exit.
    cond_signal(&reaction->has_enough_o, &reaction->lock);
    cond_signal(&reaction->has_enough_o, &reaction->lock);

    // Make water.
    reaction->h -= 2;
    reaction->o -= 1;
    make_water();

    lock_release(&reaction->lock);
}
