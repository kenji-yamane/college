#ifndef TRELLIS_H
#define TRELLIS_H

#include <vector>
#include "../binary/binary.h"

struct Edge {
	int begin;
	int end;
	int input;
	int output;
};

class Trellis {
public:
	Trellis(int, std::vector<int>, Binary*);
	std::vector<Edge> getTransitions(int);
	Edge getTransition(int, int);

private:
	int numStates;
	std::vector<int> g;
	Binary *bin;
};

#endif

