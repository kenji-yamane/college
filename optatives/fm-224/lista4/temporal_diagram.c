#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "solve.h"

enum PERIOD {
	ONE = 0,
	THREE,
	SIX
};

#define DISCARDED 1000
#define CONV 1000
#define ORBIT_LEN 20000
#define EPSILON 1e-3

#define FRAMES_PER_PERIOD 30
#define STEP 2*M_PI/FRAMES_PER_PERIOD

void stochastic_stroboscopic_map(double orbit_point[3]) {
	for (int i = 0; i < FRAMES_PER_PERIOD; i++) {
		rk_fourth_order(orbit_point, STEP, true);
	}
}

void stroboscopic_map(double orbit_point[3]) {
	for (int i = 0; i < FRAMES_PER_PERIOD; i++) {
		rk_fourth_order(orbit_point, STEP, false);
	}
}

enum PERIOD which_attractor(double orbit_point[3]) {
	double previous_bz;
	double predict_point[3] = {orbit_point[0], orbit_point[1], orbit_point[2]};

	for (int i = 0; i < CONV; i++) {
		stroboscopic_map(predict_point);
	}

	previous_bz = predict_point[1];
	stroboscopic_map(predict_point);
	if (fabs(predict_point[1] - previous_bz) < EPSILON) return ONE;

	previous_bz = predict_point[1];
	for (int i = 0; i < 3; i++) stroboscopic_map(predict_point);
	if (fabs(predict_point[1] - previous_bz) < EPSILON) return THREE;

	return SIX;
}

int main() {
	double pTime = 0;
	srand(time(NULL));
    
	FILE *s = fopen("diagram.txt", "w");

	double orbit_point[3] = {-0.9, 1, 0};
	for (int i = 0; i < DISCARDED; i++) {
		stochastic_stroboscopic_map(orbit_point);
		pTime += 2*M_PI;
	}
	for (int i = 0; i < ORBIT_LEN; i++) {
		stochastic_stroboscopic_map(orbit_point);
		pTime += 2*M_PI;
		fprintf(s, "%lf, %lf, %d\n", pTime, orbit_point[1], which_attractor(orbit_point));
	}

	fclose(s);

	return 0;
}

