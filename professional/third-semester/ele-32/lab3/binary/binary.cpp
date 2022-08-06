#include "binary.h"

#include <iostream>
#include <bitset>
#include <cmath>

Binary::Binary(int n) : maxNumBits(n) {
	this->numberOfOnes = std::vector<int>(1 << this->maxNumBits, 0);
	for (int i = 0; i < (1 << this->maxNumBits); i++) {
		this->numberOfOnes[i] = this->inefficientCountSetBits(i);
	}
}

int Binary::countSetBits(int n) {
	if (n >= (1 << this->maxNumBits)) {
		std::cout << "[BINARY] too many bits, cannot compute" << std::endl;
		exit(0);
	}
	return this->numberOfOnes[n];
}

int Binary::hammingDistance(int b1, int b2) {
	return this->countSetBits(b1 ^ b2);
}

std::vector<double> Binary::binary3ToBPSK(int x) {
	std::bitset<3> bits(x);
	std::vector<double> bpsk;
	for (int i = 0; i < 3; i++) {
		bpsk.push_back(this->binaryToBPSK(bits[i]));
	}
	return bpsk;
}

double Binary::binaryToBPSK(int x) {
	double mask[2] = {-1, 1};
	return mask[x];
}

double Binary::quadraticDistance(std::vector<double> &v1, std::vector<double> &v2) {
	double dist = 0;
	for (int i = 0; i < (int)v1.size(); i++) {
		dist += (v1[i] - v2[i])*(v1[i] - v2[i]);
	}
	return dist;
}

void Binary::populateLogprob(double p) {
	this->logprobDistance.clear();
	for (int i = 0; i < (1 << 6); i++) {
		int upperHalf = (i >> 3);
		int lowHalf = i - (upperHalf << 3);
		this->logprobDistance.push_back(this->inefficientLogprob(lowHalf, upperHalf, p));
	}
}

double Binary::logprob(int b1, int b2) {
	return this->logprobDistance[(b1 << 3) + b2];
}

int Binary::inefficientCountSetBits(int n) {
	if (n == 0) {
		return 0;
	}
	return 1 + inefficientCountSetBits(n & (n - 1));
}

double Binary::inefficientLogprob(int b1, int b2, double p) {
	int hamm = this->hammingDistance(b1, b2);
	return (3 - hamm)*std::log(1 - p) + hamm*std::log(p);
}

