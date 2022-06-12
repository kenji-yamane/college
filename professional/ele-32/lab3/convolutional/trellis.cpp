#include "trellis.h"

#include <cmath>

Trellis::Trellis(int numStates, std::vector<int> g, Binary *b) : numStates(numStates), g(g), bin(b) {
}

std::vector<Edge> Trellis::getTransitions(int stateArray) {
	Edge edgeWithZero, edgeWithOne;
	
	edgeWithZero = this->getTransition(stateArray, 0);
	edgeWithOne = this->getTransition(stateArray, 1);

	return std::vector<Edge>{edgeWithZero, edgeWithOne};
}

Edge Trellis::getTransition(int stateArray, int input) {
	Edge transition{stateArray, -1, input, 0};
	int a = (stateArray >> 1);

	switch (input) {
		case 0:
			transition.end = a;
			for (int i = 0; i < (int)g.size(); i++) {
				int shift = g.size() - i - 1;
				int bitOut = this->bin->countSetBits(stateArray & g[i])%2;
				transition.output += (bitOut << shift);
			}
			break;
		case 1:
			transition.end = (1 << (this->numStates - 1)) + a;
			int stateArrayWithPrependedOne = (1 << this->numStates) + stateArray;
			for (int i = 0; i < (int)g.size(); i++) {
				int shift = g.size() - i - 1;
				int bitOut = this->bin->countSetBits(stateArrayWithPrependedOne & g[i])%2;
				transition.output += (bitOut << shift);
			}
			break;
	}
	return transition;
}

