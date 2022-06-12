#include "bsc_canal.h"

BscCanal::BscCanal(double p, Random *r) : p(p), r(r) {
}

int BscCanal::transmit(int x) {
	if (this->errorHappened()) {
		return 1 - x;
	}
	return x;
}

bool BscCanal::errorHappened() {
	double u = this->r->uniformZeroOne();
	return (u <= this->p);
}

