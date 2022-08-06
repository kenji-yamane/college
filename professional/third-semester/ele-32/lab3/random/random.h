#ifndef RANDOM_H
#define RANDOM_H

#include <random>

class Random {
public:
	Random();
	double uniformZeroOne();
	int coinFlip();

private:
	std::mt19937 gen;
	std::uniform_real_distribution<double> uniformReal;
	std::uniform_int_distribution<int> uniformDiscrete;
};

#endif

