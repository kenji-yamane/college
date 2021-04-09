#include "solve.h"

void matrix_mult(double A[3][3], double b[3]) {
	double b1 = b[0];
	double b2 = b[1];
	double b3 = b[2];
	b[0] = A[0][0]*b1 + A[0][1]*b2 + A[0][2]*b3;
	b[1] = A[1][0]*b1 + A[1][1]*b2 + A[1][2]*b3;
	b[2] = A[2][0]*b1 + A[2][1]*b2 + A[2][2]*b3;
}

void mhd_map(double phases[3], bool noise) {
    double a = 0.1, omega = -1, lamb = 1.0/4, v = 0.01746;
    double by = phases[0], bz = phases[1], theta = phases[2];

	double Ainv[3][3] = {{1/(v*v+1),v/(v*v+1),0},{-v/(v*v+1),1/(v*v+1),0},{0,0,1}};

    phases[0] = pow(by,2)*bz + pow(bz,3) - (lamb + 1)*bz + a*cos(theta);
    phases[1] = -pow(by,3) - by*pow(bz,2) + (lamb + 1)*by - lamb + a*sin(theta);
    phases[2] = omega;

	if (noise) {
		// adding noise
		double noiseA = 0.058;
		phases[0] += 2*noiseA*rand()/RAND_MAX - noiseA;
		phases[1] += 2*noiseA*rand()/RAND_MAX - noiseA;
	}

	matrix_mult(Ainv,phases);
}

void scalar_mult(double factor, double vec[3]) {
	for (int i = 0; i < 3; i++) {
		vec[i] *= factor;
	}
}

void scalar_div(double factor, double vec[3]) {
	for (int i = 0; i < 3; i++) {
		vec[i] /= factor;
	}
}

void array_sum(double vec1[3], double vec2[3]) {
	for (int i = 0; i < 3; i++) {
		vec1[i] = vec1[i] + vec2[i];
	}
}

void rk_fourth_order(double phases[3], double step, bool noise) {
	double phases1[3] = {phases[0], phases[1], phases[2]};
	mhd_map(phases1, noise);
	scalar_mult(step, phases1);

	double phases2[3] = {phases1[0], phases1[1], phases1[2]};
	scalar_mult(0.5, phases2);
	array_sum(phases2, phases);
	mhd_map(phases2, noise);
	scalar_mult(step, phases2);

	double phases3[3] = {phases2[0], phases2[1], phases2[2]};
	scalar_mult(0.5, phases3);
	array_sum(phases3, phases);
	mhd_map(phases3, noise);
	scalar_mult(step, phases3);

	double phases4[3] = {phases3[0], phases3[1], phases3[2]};
	array_sum(phases4, phases);
	mhd_map(phases4, noise);
	scalar_mult(step, phases4);

	scalar_div(6, phases1);
	array_sum(phases, phases1);
	scalar_div(3, phases2);
	array_sum(phases, phases2);
	scalar_div(3, phases3);
	array_sum(phases, phases3);
	scalar_div(6, phases4);
	array_sum(phases, phases4);
}

