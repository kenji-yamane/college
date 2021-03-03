#include <iostream>
#include <fstream>
#include <utility>

#include <cmath>
#include <cstring>

#define ORBIT_SIZE 1000


void henon_map(double arr[]) {
	double x = arr[0], y = arr[1];

	arr[0] = 1.4 - x*x + 0.3*y;
	arr[1] = x;
}

int main() {
	double arr[2] = {0, 0};
	double dist[1000000], dx, dy;
	int len = 0;
	std::pair<double, double> orbit[ORBIT_SIZE + 1];
	std::ofstream o("corr.txt", std::ofstream::out);

	for (int i = 0; i < 2*ORBIT_SIZE; i++) {
		if (i >= ORBIT_SIZE) {
			orbit[i - ORBIT_SIZE].first = arr[0];
			orbit[i - ORBIT_SIZE].second = arr[1];
		}
		henon_map(arr);
	}

	for (int i = 0; i < ORBIT_SIZE; i++) {
		for (int j = i + 1; j < ORBIT_SIZE; j++) {
			dx = orbit[i].first - orbit[j].first;
			dy = orbit[i].second - orbit[j].second;
			dist[len++] = sqrt(dx*dx + dy*dy);
		}
	}

	double C = 0;
	double choose2 = ORBIT_SIZE*(ORBIT_SIZE - 1)/2;
	for (int res = 4; res <= 256; res *= 2) {
		for (int i = 0; i < len; i++) {
			if (dist[i] < 1.0/res) {
				C += 1;
			}
		}
		o << log2(1.0/res) << ",";
		o << log2(C/choose2) << std::endl;
		C = 0;
	}

	o.close();

	return 0;
}

