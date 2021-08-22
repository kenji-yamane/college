#ifndef LORENTZ_H
#define LORENTZ_H

#include <Eigen/Dense>

enum Dimensions {
	x = 0,
	y,
	z,
	J11,
	J12,
	J13,
	J21,
	J22,
	J23,
	J31,
	J32,
	J33
};

struct LorentzParams {
	double sigma;
	double r;
	double b;
};

Eigen::VectorXd lorentzFunction(const Eigen::VectorXd &point, const LorentzParams &params);

Eigen::VectorXd lorentzVariational(const Eigen::VectorXd &point, const LorentzParams &params);

#endif // LORENTZ_H

