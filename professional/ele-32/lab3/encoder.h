#ifndef ENCODER_H
#define ENCODER_H

#include "trellis.h"

struct Node {
	int parent;
	int cost;
	int input;
};

class Encoder {
public:
	Encoder(int numStates, std::vector<int> g);
	int encode(int input);
	void decode(int output);
	std::vector<int> getSequence();

private:
	int stateArray;
	Trellis t;
	
	std::vector<std::vector<Node> > stateSequence;
};

#endif

