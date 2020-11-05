#include <iostream>
#include <fstream>

#include <cmath>
#include <cstring>

#define ORBIT_SIZE 10000000


void henon_map(double arr[]) {
	double x = arr[0], y = arr[1];

	arr[0] = 1.4 - x*x + 0.3*y;
	arr[1] = x;
}

int main() {
	int marked = 0;
	double orbit[2] = {0, 0};
	bool grid[1024][1024] = {};
	std::ofstream o("boxes.txt", std::ofstream::out);

	for (int res = 8; res <= 256; res *= 2) {
		for (int i = 0; i < ORBIT_SIZE; i++) {
			if (i > 1000) {
				int i = floor(res*orbit[0] + 2*res);
				int j = floor(res*orbit[1] + 2*res);
				grid[i][j] = true;
				henon_map(orbit);
			}
		}

		for (int i = 0; i < 1024; i++) {
			for (int j = 0; j < 1024; j++) {
				if (grid[i][j]) {
					marked++;
				}
			}
		}

		o << log2(res) << ",";
		o << log2(marked) << std::endl;
		memset(grid, sizeof(grid), false);
		marked = 0;
	}

	o.close();

	return 0;
}

