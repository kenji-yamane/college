#ifndef RANDOM_H
#define RANDOM_H

#include <random>

class Random {
public:
	Random();
	double uniformZeroOne();
	int coinFlip();
	void setNormal(double mean, double stddev);
	double normal();

private:
	std::mt19937 gen;
	std::uniform_real_distribution<double> uniformReal;
	std::uniform_int_distribution<int> uniformDiscrete;
	std::normal_distribution<double> normalReal;
};

#endif

