#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define min(x, y) ((x) < (y) ? (x) : (y))
#define max(x, y) ((x) > (y) ? (x) : (y))
#define inbox(y) (y[0] >= boxmin[0] && y[0] <= boxmax[0] && \
				  y[1] >= boxmin[1] && y[1] <= boxmax[1])

#define SMALL 1.0e-06
#define JUMP 1.0e-03
#define TINY 1.0e-16

double modval[2] = {0.0, 0.0};

// saddle: -1.954798835069989 or -2
// saddle: 0.6547988350699888 or 0.7

double endpoint[2] = {-1.6437171043518959, -1.6437171043518959};

//double stable_manifold = (-2*saddle + sqrt(4*saddle*saddle - 1.2))/2;
//double unstable_manifold = (-2*saddle - sqrt(4*saddle*saddle - 1.2))/2;

// stable: 0.07830250264858352 or 0.07646159383286544
// unstable: 3.8312951674913944 or 3.9235384061671343

// stable: -0.2959652881307228 or -0.2641101056459327
// unstable: -1.0136323820092548 or -1.1358898943540672

double dgamma[2] = {JUMP*0.37809238938344136, JUMP};

double boxmin[2] = {-2.5, -2.5};
double boxmax[2] = {5, 5};
double dbox[2] = {7.5, 7.5};

// alpha: 1.28 or 1.4
double alpha = -0.75, beta = -1.1;

void map(double *y, int m) {
	int j;
	double xnext, ynext;

	for (j = 0; j < m*2; j++) {
		xnext = y[1];
		ynext = (y[1]*y[1] + y[0] - alpha)/beta;
		y[0] = xnext;
		y[1] = ynext;
		//xnext = alpha - y[0]*y[0] + beta*y[1];
		//ynext = y[0];
		//y[0] = xnext;
		//y[1] = ynext;
	}

	return;
}

double ychange(double s, double *y, double *yc, int m) {
	double dx, dy;

	yc[0] = endpoint[0] + s*dgamma[0];
	yc[1] = endpoint[1] + s*dgamma[1];
	map(yc, m);

	dx = fabs(y[0] - yc[0] - modval[0])/dbox[0];
	dy = fabs(y[1] - yc[1] - modval[1])/dbox[1];
	dx = max(dx, dy);

	return max(dx, SMALL);
}

double revise(double s, double ds, double *y, double *yc, int m) {
	double previous = ds, delta;

	while (((delta = ychange(s + ds, y, yc, m)) > JUMP ||
		   (ds *= 0.2 + 0.8/delta) <= previous*0.5) && ds > TINY) {
		ds = previous = previous*0.5;
	}
	ds = min(ds, previous*2.0);

	if (ds < TINY) {
		fprintf(stderr, "stepsize reset from %lg to ", ds);
		fprintf(stderr, "%lg at s = %lg, m = %d\n", TINY, s, m);
	}

	return max(ds, TINY);
}

int iterate(double s, double *y, int m, int n) {
	double prev[2];
	int ok;
	
	if (m == 0 || !inbox(y)) {
		y[0] = endpoint[0] + s*dgamma[0];
		y[1] = endpoint[1] + s*dgamma[1];
		m = 0;
	}
	
	prev[0] = y[0];
	prev[1] = y[1];
	if (m < n) do {
		map(y, 1);
		if (ok = inbox(y)) {
			prev[0] = y[0];
			prev[1] = y[1];
		} else {
			y[0] = prev[0];
			y[1] = prev[1];
		}
	} while (ok && ++m < n);

	return m;
}

int main(int argc, char **argv) {
	int ok = 0, m = 0;
	double s, y[2], yc[2];
	int n = atoi(argv[1]);
	double ds = 1.0e-15;
	double smax = atof(argv[2]);

	FILE *out = fopen("stable.txt", "w");

	for (s = 0.0; s < smax; s = min(s + ds, smax)) {
		if (!ok || m < n) {
			m = iterate(s, y, m, n);
		}
		ds = revise(s, ds, y, yc, m);

		if (m < n) {
			map(y, 1);
			map(yc, 1);
			if (inbox(y) || inbox(yc)) {
				ds = revise(s, ds, y, yc, ++m);
			}
		}
		y[0] = yc[0];
		y[1] = yc[1];

		if ((ok = inbox(y)) && m == n) {
			fprintf(out, "%lf,%lf\n", y[0], y[1]);
		}
	}

	fclose(out);

	return 0;
}

