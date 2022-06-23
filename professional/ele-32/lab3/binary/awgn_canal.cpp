#include "awgn_canal.h"

#include <cmath>
#include <iostream>

AwgnCanal::AwgnCanal(double p, Random *r) : r(r) {
	std::cout << p << std::endl;
	double snr = std::log(1/2/p);
	this->stddev = std::sqrt(snr);
	std::random_device rd;
	this->gen = std::mt19937(rd());
	std::cout << snr << std::endl;
	this->normalReal = std::normal_distribution<double>(0, this->stddev);
}

double AwgnCanal::transmit(double x) {
	return x + this->normalReal(this->gen);
}

