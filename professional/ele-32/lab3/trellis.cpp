#include "trellis.h"

#include <cmath>

Trellis::Trellis(int numStates, std::vector<int> g) : numStates(numStates), g(g) {
	for (int i = 0; i < 128; i++) {
		this->numberOfOnes[i] = this->countSetBits(i);
	}
}

std::vector<Edge> Trellis::getTransitions(int stateArray) {
	Edge edgeWithZero, edgeWithOne;

	edgeWithZero.begin = edgeWithOne.begin = stateArray;
	edgeWithZero.input = 0;
	edgeWithOne.input = 1;

	int a = (stateArray >> 1);
	edgeWithZero.end = a;
	edgeWithOne.end = (1 << (this->numStates - 1)) + a;

	edgeWithZero.output = 0;
	for (int i = 0; i < g.size(); i++) {
		int shift = g.size() - i - 1;
		int bitOut = this->numberOfOnes[(stateArray & g[i])]%2;
		edgeWithZero.output += (bitOut << shift);
	}

	edgeWithOne.output = 0;
	int stateArrayWithPrependedOne = (1 << this->numStates) + stateArray;
	for (int i = 0; i < g.size(); i++) {
		int shift = g.size() - i - 1;
		int bitOut = this->numberOfOnes[(stateArrayWithPrependedOne & g[i])]%2;
		edgeWithOne.output += (bitOut << shift);
	}

	return std::vector<Edge>{edgeWithZero, edgeWithOne};
}

int Trellis::countSetBits(int n) {
	if (n == 0) {
		return 0;
	}
	return 1 + countSetBits(n & (n - 1));
}

int Trellis::getNumberOfOnes(int n) {
	return this->numberOfOnes[n];
}

