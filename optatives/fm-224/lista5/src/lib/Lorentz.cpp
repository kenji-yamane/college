#include "Lorentz.h"

Eigen::VectorXd lorentzFunction(const Eigen::VectorXd &point, const LorentzParams &params) {
	Eigen::VectorXd next(3);

	next << params.sigma*(point(1) - point(0)),
			params.r*point(0) - point(1) - point(0)*point(2),
			-params.b*point(2) + point(0)*point(1);
	
	return next;
}

