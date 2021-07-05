#include "Lorentz.h"

Eigen::VectorXd lorentzFunction(const Eigen::VectorXd &point, const LorentzParams &params) {
	Eigen::VectorXd next(3);

	next << params.sigma*(point(y) - point(x)),
			params.r*point(x) - point(y) - point(x)*point(z),
			-params.b*point(z) + point(x)*point(y);
	
	return next;
}

Eigen::VectorXd lorentzVariational(const Eigen::VectorXd &point, const LorentzParams &params) {
	Eigen::VectorXd next(12);

	next << params.sigma*(point(y) - point(x)),
			params.r*point(x) - point(y) - point(x)*point(z),
			-params.b*point(z) + point(x)*point(y),
			params.sigma*(point(J21) - point(J11)),
			params.sigma*(point(J22) - point(J12)),
			params.sigma*(point(J23) - point(J13)),
			(params.r - point(z))*point(J11) - point(J21) - point(x)*point(J31),
			(params.r - point(z))*point(J12) - point(J22) - point(x)*point(J32),
			(params.r - point(z))*point(J13) - point(J23) - point(x)*point(J33),
			point(y)*point(J11) + point(x)*point(J21) - params.b*point(J31),
			point(y)*point(J12) + point(x)*point(J22) - params.b*point(J32),
			point(y)*point(J13) + point(x)*point(J23) - params.b*point(J33);
	
	return next;
}

