#include <iostream>
#include <fstream>
#include <Eigen/Dense>

#include "lib/RungeKutta.h"
#include "lib/Lorentz.h"

#define CONV 1000
#define ORBIT_LEN 20000

int main() {
	LorentzParams params = {
		10,
		28,
		8.0/3
	};
	RungeKutta rungeKutta(0.0039, [&, params](const Eigen::VectorXd &point) {
		return lorentzFunction(point, params);
	});

	Eigen::VectorXd orbitPoint(3);
	orbitPoint << 1, 1, 1;
	for (int i = 0; i < 10*CONV; i++) {
		rungeKutta.fourthOrder(orbitPoint);
	}

	std::ofstream time_series("../logs/lorentz_time_series.txt");
	for (int i = 0; i < ORBIT_LEN; i++) {
		for (int j = 0; j < 4; j++) rungeKutta.fourthOrder(orbitPoint);
		time_series << orbitPoint(0) << std::endl;
	}
	time_series.close();

	return 0;
}

