#ifndef LORENTZ_H
#define LORENTZ_H

#include <Eigen/Dense>

struct LorentzParams {
	double sigma;
	double r;
	double b;
};

Eigen::VectorXd lorentzFunction(const Eigen::VectorXd &point, const LorentzParams &params);

#endif // LORENTZ_H

