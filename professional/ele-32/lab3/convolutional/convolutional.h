#ifndef CONVOlUTIONAL_H
#define CONVOLUTIONAL_H

#include "trellis.h"
#include "../binary/binary.h"

struct Node {
	int parent;
	int cost;
	int input;
};

class Convolutional {
public:
	Convolutional(int, std::vector<int>, Binary*);
	int encode(int);
	void decode(int);
	std::vector<int> getSequence();

private:
	int stateArray;
	Trellis t;
	Binary *bin;
	
	std::vector<std::vector<Node> > stateSequence;
};

#endif

