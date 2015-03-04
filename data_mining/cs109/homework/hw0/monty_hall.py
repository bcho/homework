from __future__ import print_function

import numpy as np

DOORS = 3
GAME_TIMES = 10000


def simulate_prizedoor(nsim):
    return np.random.choice(DOORS, nsim)


def simulate_guess(nsim):
    return np.zeros(nsim, dtype=np.int)


def goat_door(prizedoors, guesses):
    result = np.random.choice(DOORS, prizedoors.size)
    while True:
        bad = (result == prizedoors) | (result == guesses)
        if not bad.any():
            return result
        result[bad] = np.random.randint(0, 3, bad.sum())


def switch_guess(guesses, goatdoors):
    result = np.zeros(guesses.size)
    switch = {
        (0, 1): 2, (0, 2): 1, (1, 0): 2,
        (1, 2): 0, (2, 0): 1, (2, 1): 0
    }
    for i in [0, 1, 2]:
        for j in [0, 1, 2]:
            mask = (guesses == i) & (goatdoors == j)
            if not mask.any():
                continue
            result = np.where(mask, np.ones_like(result) * switch[(i, j)],
                              result)
    return result


def win_percentage(guesses, prizedoors):
    return 100 * (guesses == prizedoors).mean()


# keep gusses
print('Keeping original door:')
print(win_percentage(
    simulate_prizedoor(GAME_TIMES),
    simulate_guess(GAME_TIMES)
))


# switch after revealed
print('Switch after revealed:')
prize_doors = simulate_prizedoor(GAME_TIMES)
guess = simulate_guess(GAME_TIMES)
goats = goat_door(prize_doors, guess)
guess = switch_guess(guess, goats)
print(win_percentage(prize_doors, guess))
