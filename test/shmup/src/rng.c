#include <stdlib.h>
#include <time.h>

#define SEED_UNASSIGNED -1

static int seed = SEED_UNASSIGNED;

static void set_seed() {
	if (seed != SEED_UNASSIGNED) return;
	seed = time(NULL);
	srand(seed);
}

float mason_randf_range(float min, float max) {
	set_seed();
	return ((float)rand() / (float)RAND_MAX) * (max-min) + min;
}

int mason_randi_range(int min, int max) {
	set_seed();
	return rand() % (max-min) + min;
}

