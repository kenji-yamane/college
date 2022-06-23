#include "awgn_canal.h"

#include <cmath>
#include <iostream>

AwgnCanal::AwgnCanal(double snr) {
	std::random_device rd;
	this->gen = std::mt19937(rd());

	if (snr < 1e-4) {
		this->stddev = -1;
		this->normalInfinite = std::uniform_real_distribution<double>(-1e3, 1e3);
	} else {
		this->stddev = 1/std::sqrt(snr);
		this->normalReal = std::normal_distribution<double>(0, this->stddev);
	}
}

double AwgnCanal::transmit(double x) {
	if (this->stddev < 0) {
		return this->normalInfinite(this->gen);
	} else {
		return x + this->normalReal(this->gen);
	}
}

