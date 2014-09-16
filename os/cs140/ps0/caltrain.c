#include "pintos_thread.h"

struct station {
    int waiting_passengers;
    int boarding_passengers;
    int free_seats;

    struct lock lock;
    struct condition has_waiting_seats;        /* for passenger threads */
};

void
station_init(struct station *station)
{
    station->waiting_passengers = 0;
    station->boarding_passengers = 0;
    station->free_seats = 0;

    lock_init(&station->lock);
    cond_init(&station->has_waiting_seats);
}

void
station_load_train(struct station *station, int count)
{
    /* Has no available seat, just let the train pass by. */
    if (count <= 0)
        return;

    lock_acquire(&station->lock);
    station->free_seats = count;
    station->boarding_passengers = 0;
    while (station->waiting_passengers > 0 && station->free_seats > 0) {
        /* Notify there are available seats. */
        cond_signal(&station->has_waiting_seats, &station->lock);
        lock_release(&station->lock);
        lock_acquire(&station->lock);
    }
    /* Waiting until all passengers onboarded. */
    while (station->boarding_passengers > 0) {
        lock_release(&station->lock);
        lock_acquire(&station->lock);
    }
    /* Train is leaving, mark there is no seat available. */
    station->free_seats = 0;
    lock_release(&station->lock);
}

void
station_wait_for_train(struct station *station)
{
    lock_acquire(&station->lock);

    /* Wait for seat. */
    station->waiting_passengers = station->waiting_passengers + 1;
    while (station->free_seats <= 0) {
        cond_wait(&station->has_waiting_seats, &station->lock);
    }

    /* Book the seat. */
    station->free_seats = station->free_seats - 1;
    /* Boarding */
    station->boarding_passengers = station->boarding_passengers + 1;

    lock_release(&station->lock);

    // Will call station_on_board after this returns.
}

void
station_on_board(struct station *station)
{
    lock_acquire(&station->lock);
    station->waiting_passengers = station->waiting_passengers - 1;
    station->boarding_passengers = station->boarding_passengers - 1;
    lock_release(&station->lock);
}
