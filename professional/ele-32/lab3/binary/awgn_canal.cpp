#include "awgn_canal.h"

#include <cmath>

AwgnCanal::AwgnCanal(double p, Random *r) : r(r) {
	double snr = std::log(1/2/p);
	this->stddev = std::sqrt(snr);
	r->setNormal(0, this->stddev);
}

double AwgnCanal::transmit(double x) {
	return x + r->normal();
}

