#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define SPATIAL_SIZE 1024
#define PRINT_RANGE 50
#define SPATIAL_LEN 536
#define VVALUE 0.625
#define DELTA_X 1.0*SPATIAL_LEN/SPATIAL_SIZE
#define DELTA_T 0.01

double nextF[SPATIAL_SIZE];
double f[SPATIAL_SIZE];

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
	for (int i = 0; i < SPATIAL_SIZE; i++) {
		f[i] = nextF[i];
	}
}

void printState(FILE *out) {
	for (int i = 0; i < PRINT_RANGE; i++) {
		fprintf(out, "%lf\n", f[i]);
	}
}

void printFullState(FILE *out) {
	for (int i = 0; i < SPATIAL_SIZE; i++) {
		fprintf(out, "%lf\n", f[i]);
	}
}

int main() {
	//FILE *init_c = fopen("initial_conditions.txt", "w");
	FILE *init_c = fopen("initial_conditions.txt", "r");
	FILE *s = fopen("kuramoto_out.txt", "w");
	//FILE *s2 = fopen("complete_kuramoto.txt", "w");
	srand(time(NULL));

	for (int i = 0; i < SPATIAL_SIZE; i++) {
		f[i] = 1;
		//fscanf(init_c, "%lf", &f[i]);
		//f[i] = 20*(double)rand()/RAND_MAX - 0.001;
		//fprintf(init_c, "%lf\n", f[i]);
	}
	for (int i = 0; i < 200000; i++) {
		integrate();
	}
	for (int i = 0; i < 10001; i++) {
		integrate();
		//printFullState(s2);
		printState(s);
	}

	fclose(init_c);
	fclose(s);
	//fclose(s2);

	return 0;
}

