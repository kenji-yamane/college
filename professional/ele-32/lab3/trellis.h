#ifndef TRELLIS
#define TRELLIS

#include <vector>

struct Edge {
	int begin;
	int end;
	int input;
	int output;
};

class Trellis {
public:
	Trellis(int numStates, std::vector<int> g);
	std::vector<Edge> getTransitions(int stateArray);
	int getNumberOfOnes(int n);

private:
	int numberOfOnes[128];
	int numStates;
	std::vector<int> g;

	int countSetBits(int n);
};

#endif

