#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "solve.h"

/*
To generate everything:
V_SPACE_BEGIN: 0.014
V_SPACE_END: 0.024
V_SPACE_LENGTH: 600

RANDOM_PARTICLES: 20
CONV 1000
ORBIT 200
verification: none
*/

/*
To generate figure 1:
V_SPACE_BEGIN: 0.014
V_SPACE_END: 0.024
V_SPACE_LENGTH: 500
    
RANDOM_PARTICLES: 15
CONV 900
ORBIT 200
verification: is_valid_point_1
*/

/*
To generate figure 2:
V_SPACE_BEGIN: 0.0174
V_SPACE_END: 0.0179
V_SPACE_LENGTH: 400

RANDOM_PARTICLES: 15
CONV 400
ORBIT 1000
verification: is_valid_point_2
*/

#define V_SPACE_BEGIN 0.014
#define V_SPACE_END 0.024
#define V_SPACE_LENGTH 500

#define RANDOM_PARTICLES 20
#define CONV 200
#define ORBIT 100

bool is_valid_point_1(double bz, double v) {
	bool valid = true;

	if (bz < -1.25) {
		valid = false;
	}
	if (v < 0.0175 && bz > 0.51 && bz < 0.7) {
		valid = false;
	}
	if (v < 0.0175 && bz < 0.48 && bz > 0.4) {
		valid = false;
	}
	if (bz > -0.7 && bz < 0.45) {
		valid = false;
	}

	return valid;
}

bool is_valid_point_2(double bz, double v) {
	return bz < 0.54 && bz > 0.46;
}

bool is_valid_point_A1(double orbit_point[3], double v) {
	bool valid = true;
	double check_point[3] = {orbit_point[0], orbit_point[1], orbit_point[2]};
	for (int i = 0; i < FRAMES_PER_PERIOD; i++) {
		rk_fourth_order(check_point, v);
	}
	if (fabs(orbit_point[1] - check_point[1]) > 5e-3) {
		valid = false;
	}

	return valid;
}

bool is_valid_point_A2(double orbit_point[3], double v) {
	if (orbit_point[1] > 0.7 && orbit_point[1] < 0.8) {
		return false;
	}
	if (orbit_point[1] < 0.46 && orbit_point[1] > -0.75) {
		return false;
	}
	if (v < 0.0147 || orbit_point[1] < -1.5) {
		return false;
	}
	if (v < 0.016 || v > 0.018) {
		return true;
	}

	bool three = true, six = true;
	double check_point[3] = {orbit_point[0], orbit_point[1], orbit_point[2]};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < FRAMES_PER_PERIOD; j++) {
			rk_fourth_order(check_point, v);
		}
	}
	if (fabs(orbit_point[1] - check_point[1]) > 5e-3) {
		three = false;
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < FRAMES_PER_PERIOD; j++) {
			rk_fourth_order(check_point, v);
		}
	}
	if (fabs(orbit_point[1] - check_point[1]) > 5e-3) {
		six = false;
	}

	return (three || six);
}

bool is_valid_point_A3(double orbit_point[3], double v) {
	if (orbit_point[1] < -1.3) {
		return false;
	}
	if (orbit_point[1] > -0.55 && orbit_point[1] < 0.42) {
		return false;
	}
	if (orbit_point[1] > 0.6 && orbit_point[1] < 0.8) {
		return false;
	}

	double check_point[3] = {orbit_point[0], orbit_point[1], orbit_point[2]};
	double bz_period[3];
	bool valid = true;


	for (int i = 0; i < 3; i++) {
		bz_period[i] = check_point[1];
		for (int j = 0; j < FRAMES_PER_PERIOD; j++) {
			rk_fourth_order(check_point, v);
		}
	}
	if (fabs(orbit_point[1] - check_point[1]) < 1e-2) {
		for (int i = 0; i < 3; i++) {
			if (bz_period[i] > 0.477 && bz_period[i] < 0.485) {
				valid = false;
			}
		}
	}

	return valid;
}

bool is_valid_point_A4(double orbit_point[3], double v) {
	if (orbit_point[1] < -1.4) {
		return true;
	}
	if (orbit_point[1] > -0.55 && orbit_point[1] < 0.46) {
		return true;
	}
	
	if (v < 0.01725 && orbit_point[1] > -0.75) {
		return true;
		double check_point[3] = {orbit_point[0], orbit_point[1], orbit_point[2]};
		for (int j = 0; j < 3; j++) {
			for (int j = 0; j < FRAMES_PER_PERIOD; j++) {
				rk_fourth_order(check_point, v);
			}
		}
		double three = check_point[1];
		for (int j = 0; j < 6; j++) {
			for (int j = 0; j < FRAMES_PER_PERIOD; j++) {
				rk_fourth_order(check_point, v);
			}
		}
		double six = check_point[1];
		if (fabs(three - orbit_point[1]) > 1e-2 && fabs(six - orbit_point[1]) > 1e-2) {
			return true;
		}
	}

	return false;
}

int main() {
	srand(time(NULL));
    
	FILE *s = fopen("diagram.txt", "w");

	double v_space[V_SPACE_LENGTH];
	double v_step = (V_SPACE_END - V_SPACE_BEGIN)/(V_SPACE_LENGTH - 1);

	for (int i = 0; i < V_SPACE_LENGTH; i++) {
		v_space[i] = V_SPACE_BEGIN + i*v_step;
	}

	for (int i = 0; i < V_SPACE_LENGTH; i++) {
		for (int j = 0; j < RANDOM_PARTICLES; j++) {
			double by = (double)rand()/RAND_MAX*6 - 3;
			double bz = (double)rand()/RAND_MAX*6 - 3;
			double theta = 0;
			double orbit_point[3] = {by, bz, theta};

			for (int k = 0; k < CONV; k++) {
				for (int l = 0; l < FRAMES_PER_PERIOD; l++) {
					rk_fourth_order(orbit_point, v_space[i]);
				}
			}

			for (int k = 0; k < ORBIT; k++) {
				if (is_valid_point_A4(orbit_point, v_space[i])) {
					fprintf(s, "%lf,%lf\n", v_space[i], orbit_point[1]);
				}
				for (int l = 0; l < FRAMES_PER_PERIOD; l++) {
					rk_fourth_order(orbit_point, v_space[i]);
				}
			}
		}
	}

	fclose(s);

	return 0;
}

