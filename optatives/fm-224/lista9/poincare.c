#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define SPATIAL_SIZE 1024
#define PRINT_RANGE 50
#define SPATIAL_LEN 536
#define DELTA_X 1.0*SPATIAL_LEN/SPATIAL_SIZE
#define DELTA_T 0.01

double VVALUE = 0.640;
double nextF[SPATIAL_SIZE];
double f[SPATIAL_SIZE];
double timePassed;

void integrate() {
	for (int i = 0; i < SPATIAL_SIZE; i++) {
		int id = (i - 1 + SPATIAL_SIZE)%SPATIAL_SIZE,
			idd = (i - 2 + SPATIAL_SIZE)%SPATIAL_SIZE,
			is = (i + 1)%SPATIAL_SIZE,
			iss = (i + 2)%SPATIAL_SIZE;

		double dxx = DELTA_X*DELTA_X;
		double dxxxx = dxx*dxx;
		double fx = (f[is] - f[id])/(2*DELTA_X);
		double fxx = (f[is] - 2*f[i] + f[id])/dxx;
		double fxxxx = (f[iss] - 4*f[is] + 6*f[i] - 4*f[id] + f[idd])/dxxxx;
		nextF[i] = f[i] + DELTA_T*((VVALUE - 1)*f[i] - 2*fxx - fxxxx - f[i]*fx);
	}
}

void setF() {
	for (int i = 0; i < SPATIAL_SIZE; i++) {
		f[i] = nextF[i];
	}
}

void poincareMap() {
	do {
		timePassed += DELTA_T;
		setF();
		integrate();
	} while (fabs(f[5] - 3) > 0.05 || nextF[5] < f[5]);
}

void printState(FILE *out) {
	for (int i = 0; i < PRINT_RANGE; i++) {
		fprintf(out, "%lf\n", f[i]);
	}
}

void printFullState(FILE *out, double time) {
	for (int i = 0; i < SPATIAL_SIZE; i++) {
		fprintf(out, "%lf, %lf\n", f[i], time);
	}
}

int main() {
	FILE *init_c = fopen("initial_conditions.txt", "w");
	FILE *s = fopen("kuramoto_out.txt", "w");
	FILE *s2 = fopen("complete_kuramoto.txt", "w");
	srand(time(NULL));

	for (int i = 0; i < SPATIAL_SIZE; i++) {
		f[i] = 20*(double)rand()/RAND_MAX - 0.001;
		fprintf(init_c, "%lf\n", f[i]);
		nextF[i] = f[i];
	}
	for (int i = 0; i < 100000; i++) {
		integrate();
	}
	for (int i = 0; i < 1001; i++) {
		timePassed = 0;
		poincareMap();
		printFullState(s2, timePassed);
	}

	fclose(init_c);
	fclose(s);
	fclose(s2);

	return 0;
}

