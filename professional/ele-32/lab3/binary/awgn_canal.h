#ifndef AWGN_CANAL_H
#define AWGN_CANAL_H

#include "../random/random.h"

// assumes BPSK modulation
class AwgnCanal {
public:
	AwgnCanal(double, Random*);
	double transmit(double);

private:
	double stddev;
	Random *r;
};

#endif

