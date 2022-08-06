#include "random.h"

#include <algorithm>
#include <ctime>

#include <iostream>

Random::Random() {
	std::random_device rd;
	this->gen = std::mt19937(rd());
	this->uniformReal = std::uniform_real_distribution<double>(0, 1);
	this->uniformDiscrete = std::uniform_int_distribution<int>(0, 1);
}

double Random::uniformZeroOne() {
	return this->uniformReal(this->gen);
}

int Random::coinFlip() {
	return this->uniformDiscrete(this->gen);
}

