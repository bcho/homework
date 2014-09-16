/*
 * This file tests the implementation in reaction.c. You shouldn't need to
 * modify it, but you're welcome to do so. Please report any bugs to us via
 * Piazza or email (cs140ta@cs).
 *
 * Note that passing these tests doesn't guarantee that your code is correct
 * or meets the specifications given, but hopefully it's at least pretty
 * close.
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#include "reaction.c"

volatile int water_molecules = 0;
volatile int hydrogen_atoms_bonded = 0;
volatile int oxygen_atoms_bonded = 0;

void
make_water()
{
	__sync_add_and_fetch(&water_molecules, 1);
}

void*
hydrogen_thread(void *arg)
{
	struct reaction *reaction = (struct reaction*)arg;
	reaction_h(reaction);
	__sync_add_and_fetch(&hydrogen_atoms_bonded, 1);
	return NULL;
}

void*
oxygen_thread(void *arg)
{
	struct reaction *reaction = (struct reaction*)arg;
	reaction_o(reaction);
	__sync_add_and_fetch(&oxygen_atoms_bonded, 1);
	return NULL;
}

void
alarm_handler(int foo)
{
	fprintf(stderr, "Error: Failed to complete after 10 seconds. Something's "
		"wrong, or your system is terribly slow.\n");
	exit(1);
}

#ifndef MIN
#define MIN(_x,_y) ((_x) < (_y)) ? (_x) : (_y)
#endif

/*
 * This creates a bunch of threads to simulate H and O molecules. Hopefully
 * mother nature will be decent enough to bond them when asked.
 */
int
main(int argc, char** argv)
{
	struct reaction reaction;
	reaction_init(&reaction);

	if (argc != 2 || atoi(argv[1]) < 0 || atoi(argv[1]) > 100) {
		fprintf(stderr, "usage: %s percentageOfHydrogenAtoms\n"
			" e.g.: %s 50\n", argv[0], argv[0]);
		exit(1);
	}

	srandom(getpid() ^ time(NULL));

	signal(SIGALRM, alarm_handler);
	alarm(10);

	int i;
	const int total_atoms = 200;
	int hydrogen_atoms = 0;
	int oxygen_atoms = 0;
	int hydrogen_pct = atoi(argv[1]);

	for (i = 0; i < total_atoms; i++) {
		pthread_t tid;
		int ret;
		if ((random() % 100) < hydrogen_pct) {
			hydrogen_atoms++;
			ret = pthread_create(&tid, NULL, hydrogen_thread, &reaction);
		} else {
			oxygen_atoms++;
			ret = pthread_create(&tid, NULL, oxygen_thread, &reaction);
		}
		if (ret != 0) {
			// If this fails, perhaps we exceeded some system limit.
			// Try reducing 'total_atoms'.
			perror("pthread_create");
			exit(1);
		}
	}

	int expected_molecules = MIN(hydrogen_atoms / 2, oxygen_atoms);
	printf("Created %d H and %d O atoms (%.1f%% H), expecting %d H2O molecules\n",
		hydrogen_atoms, oxygen_atoms, (double)hydrogen_atoms / total_atoms * 100.0,
		expected_molecules);

	// Wait for expected reactions to complete.
	while (water_molecules != expected_molecules)
		;

	// Wait a little longer in case the student's implementation is buggy and
	// we see too many reactions.
	usleep(100000);

	if (water_molecules != expected_molecules) {
		fprintf(stderr, "Error: expected %d H20 molecules, but %d were created!\n",
			expected_molecules, water_molecules);
		exit(1);
	}

	if (hydrogen_atoms_bonded != (expected_molecules * 2)) {
		fprintf(stderr, "Error: expected %d reaction_h() calls to return, but "
			"%d did instead!\n", expected_molecules * 2,
			hydrogen_atoms_bonded);
		exit(1);
	}

	if (oxygen_atoms_bonded != expected_molecules) {
		fprintf(stderr, "Error: expected %d reaction_o() calls to return, but "
			"%d did instead!\n", expected_molecules, oxygen_atoms_bonded);
		exit(1);
	}

	printf("Looks good!\n");
	return 0;
}
