#ifndef AWGN_CANAL_H
#define AWGN_CANAL_H

#include "../random/random.h"
#include <random>

// assumes BPSK modulation
class AwgnCanal {
public:
	AwgnCanal(double, Random*);
	double transmit(double);

private:
	double stddev;
	Random *r;
	std::mt19937 gen;
	std::normal_distribution<double> normalReal;
};

#endif

