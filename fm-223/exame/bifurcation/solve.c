#include "solve.h"

void linsolve(double A[3][3], double phases[3]) {
    for (int k = 0; k < 3; k++) {
        for (int i = k+1; i < 3; i++) {
            double m = A[i][k]/A[k][k];
            A[i][k] = 0;
            for (int j = k+1; j < 3; j++) {
                A[i][j] -= m*A[k][j];
            }
            phases[i] -= m*phases[k];
        }
    }

    double x[3];
    for (int i = 2; i >= 0; i--) {
        double S = 0;
        for (int j = i; j < 3; j++) {
            S += A[i][j]*x[j];
        }
        x[i] = (phases[i]-S)/A[i][i];
    }

    for (int i = 0; i < 3; i++) {
        phases[i] = x[i];
    }
}

void matrix_mult(double A[3][3], double b[3]) {
	double b1 = b[0];
	double b2 = b[1];
	double b3 = b[2];
	b[0] = A[0][0]*b1 + A[0][1]*b2 + A[0][2]*b3;
	b[1] = A[1][0]*b1 + A[1][1]*b2 + A[1][2]*b3;
	b[2] = A[2][0]*b1 + A[2][1]*b2 + A[2][2]*b3;
}

void mhd_map(double phases[3], double v) {
    double a = 0.1, omega = -1, lamb = 1.0/4;
    double by = phases[0], bz = phases[1], theta = phases[2];

    // double A[3][3] = {{1, -v, 0},{v, 1, 0},{0, 0, 1}};
	double Ainv[3][3] = {{1/(v*v+1),v/(v*v+1),0},{-v/(v*v+1),1/(v*v+1),0},{0,0,1}};

    phases[0] = pow(by,2)*bz + pow(bz,3) - (lamb + 1)*bz + a*cos(theta);
    phases[1] = -pow(by,3) - by*pow(bz,2) + (lamb + 1)*by - lamb + a*sin(theta);
    phases[2] = omega;

	matrix_mult(Ainv,phases);
	// linsolve(A, phases);
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

void rk_second_order(double phases[3], double v) {
	double phases1[3] = {phases[0], phases[1], phases[2]};
	mhd_map(phases1, v);
	scalar_mult(STEP, phases1);

	double phases2[3] = {phases1[0], phases1[1], phases[2]};
	scalar_mult(0.5, phases2);
	array_sum(phases2, phases);
	mhd_map(phases2, v);
	scalar_mult(STEP, phases2);

	array_sum(phases, phases2);
}

void rk_fourth_order(double phases[3], double v) {
	double phases1[3] = {phases[0], phases[1], phases[2]};
	mhd_map(phases1, v);
	scalar_mult(STEP, phases1);

	double phases2[3] = {phases1[0], phases1[1], phases1[2]};
	scalar_mult(0.5, phases2);
	array_sum(phases2, phases);
	mhd_map(phases2, v);
	scalar_mult(STEP, phases2);

	double phases3[3] = {phases2[0], phases2[1], phases2[2]};
	scalar_mult(0.5, phases3);
	array_sum(phases3, phases);
	mhd_map(phases3, v);
	scalar_mult(STEP, phases3);

	double phases4[3] = {phases3[0], phases3[1], phases3[2]};
	array_sum(phases4, phases);
	mhd_map(phases4, v);
	scalar_mult(STEP, phases4);

	scalar_div(6, phases1);
	array_sum(phases, phases1);
	scalar_div(3, phases2);
	array_sum(phases, phases2);
	scalar_div(3, phases3);
	array_sum(phases, phases3);
	scalar_div(6, phases4);
	array_sum(phases, phases4);
}

