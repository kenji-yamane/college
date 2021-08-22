#include <iostream>
#include <fstream>
#include <math.h>

double ulam_map(double xn) {
	return 1 - 2*xn*xn;
}

double observation_function(double xn) {
	return std::acos(-xn)/M_PI;
}

int main() {
	std::ofstream out("../logs/ulam.txt");
	double moving_average = 0;

	double orbit_point = 0.1;
    for (int i = 0; i < 4096; i++) {
		orbit_point = ulam_map(orbit_point);
		double sample = observation_function(orbit_point);
        out << sample << std::endl;
    }

    out.close();

    return 0;
}
