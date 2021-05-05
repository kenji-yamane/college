#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <cmath>

#include "lib/RungeKutta.h"
#include "lib/Lorentz.h"

#define CONV 1000
#define ORBIT_LEN 20000

void orthogonalize(std::vector<Eigen::VectorXd> &dirs) {
	for (int i = 0; i < (int)dirs.size(); i++) {
		Eigen::VectorXd zi = dirs[i];
		for (int j = 0; j < i; j++) {
			dirs[i] -= zi.dot(dirs[j])/dirs[j].squaredNorm()*dirs[j];
		}
	}
}

int main() {
	LorentzParams params = {
		10,
		28,
        8.0/3
	};
	RungeKutta rungeKutta(0.01, [&, params](const Eigen::VectorXd &point) {
		return lorentzVariational(point, params);
	});

	Eigen::VectorXd orbitPoint(12);
	orbitPoint << 10, 1, 0, 1, 0, 0,
							0, 1, 0,
							0, 0, 1;
	
	for (int i = 0; i < CONV; i++) {
		rungeKutta.fourthOrder(orbitPoint);
	}

	Eigen::VectorXd w1(3), w2(3), w3(3);
	w1 << 1, 0, 0;
	w2 << 0, 1, 0;
	w3 << 0, 0, 1;
	std::vector<Eigen::VectorXd> ellipse = {w1, w2, w3};
	std::vector<double> lyapunovExponents = {0, 0, 0};

	for (int i = 0; i < ORBIT_LEN; i++) {
		for (int j = 0; j < 100; j++) rungeKutta.fourthOrder(orbitPoint);

		Eigen::MatrixXd jacobian(3, 3);
		jacobian << orbitPoint(J11), orbitPoint(J12), orbitPoint(J13),
					orbitPoint(J21), orbitPoint(J22), orbitPoint(J23),
					orbitPoint(J31), orbitPoint(J32), orbitPoint(J33);
		for (auto &c : ellipse) c = jacobian*c;
		orthogonalize(ellipse);
		for (int j = 0; j < (int)ellipse.size(); j++) {
			lyapunovExponents[j] += std::log2(ellipse[j].norm());
		}
		for (auto &c : ellipse) c.normalize();
		orbitPoint << orbitPoint(x), orbitPoint(y), orbitPoint(z), 1, 0, 0,
																   0, 1, 0,
																   0, 0, 1;
	}
	for (auto &c : lyapunovExponents) c /= ORBIT_LEN;
	for (const auto &c : lyapunovExponents) std::cout << c << std::endl;

	return 0;
}

