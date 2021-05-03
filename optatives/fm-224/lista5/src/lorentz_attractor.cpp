#include <iostream>
#include <fstream>
#include <vector>
#include <Eigen/Dense>

#include "lib/RungeKutta.h"
#include "lib/Lorentz.h"

#define CONV 1000
#define ORBIT_LEN 40000
#define EPSILON 0.5

int main() {
	LorentzParams params = {
		10,
		28,
		8.0/3
	};
	RungeKutta rungeKutta(0.01, [&, params](const Eigen::VectorXd &point) {
		return lorentzFunction(point, params);
	});

	Eigen::VectorXd orbitPoint(3);
	orbitPoint << 1, 1, 1;
	
	for (int i = 0; i < CONV; i++) {
		rungeKutta.fourthOrder(orbitPoint);
	}

	std::ofstream attractor("../logs/lorentz_attractor.txt");
	for (int i = 0; i < ORBIT_LEN; i++) {
		rungeKutta.fourthOrder(orbitPoint);
		attractor << orbitPoint(0) << ", ";
		attractor << orbitPoint(1) << ", ";
		attractor << orbitPoint(2) << std::endl;
	}
	attractor.close();

	std::ofstream cycle("../logs/lorentz_cycle.txt");
	double tic = rungeKutta.getTime();
	for (int i = 0; i < 157; i++) {
		rungeKutta.fourthOrder(orbitPoint);
		cycle << orbitPoint(0) << ", ";
		cycle << orbitPoint(1) << ", ";
		cycle << orbitPoint(2) << std::endl;
	}
	double tac = rungeKutta.getTime();
	cycle.close();

	std::cout << "time measured: " << tac - tic << std::endl;

	return 0;
}

