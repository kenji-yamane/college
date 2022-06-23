#include "binary.h"

#include <iostream>
#include <bitset>

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

int Binary::inefficientCountSetBits(int n) {
	if (n == 0) {
		return 0;
	}
	return 1 + inefficientCountSetBits(n & (n - 1));
}

