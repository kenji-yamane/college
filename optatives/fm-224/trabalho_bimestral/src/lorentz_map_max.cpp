#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <vector>
#include <cmath>

#include "lib/RungeKutta.h"
#include "lib/Lorentz.h"

#define CONV 1000
#define ORBIT_LEN 10000
#define D0 1e-8

int main() {
	LorentzParams params = {
		10,
		28,
		8.0/3
	};
	RungeKutta rungeKutta(0.01, [&, params](const Eigen::VectorXd &point) {
		return lorentzFunction(point, params);
	});

	Eigen::VectorXd referencePoint(3);
	referencePoint << 1, 1, 10;
	for (int i = 0; i < CONV; i++) {
		rungeKutta.fourthOrder(referencePoint);
	}

	Eigen::VectorXd travelingPoint(3);
	travelingPoint << referencePoint(0) + D0,
					  referencePoint(1),
					  referencePoint(2);
	
	std::ofstream meanConv("../logs/map_mean_convergence.txt");
	double maxLyapunov = 0;
	for (int i = 0; i < ORBIT_LEN; i++) {
		for (int j = 0; j < 100; j++) {
			rungeKutta.fourthOrder(referencePoint);
			rungeKutta.fourthOrder(travelingPoint);
		}

		double d1 = (referencePoint - travelingPoint).norm();
		maxLyapunov = (maxLyapunov*i + std::log2(d1/D0))/(i + 1);
		meanConv << maxLyapunov << std::endl;

		Eigen::VectorXd diff = travelingPoint - referencePoint;
		travelingPoint = referencePoint + diff.normalized()*D0;
	}
	meanConv.close();

	std::cout << "max lyapunov exponent estimate: ";
	std::cout << maxLyapunov << std::endl;

	return 0;
}

