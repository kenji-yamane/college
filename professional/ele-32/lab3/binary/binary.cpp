#include "binary.h"

#include <iostream>

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

int Binary::inefficientCountSetBits(int n) {
	if (n == 0) {
		return 0;
	}
	return 1 + inefficientCountSetBits(n & (n - 1));
}

