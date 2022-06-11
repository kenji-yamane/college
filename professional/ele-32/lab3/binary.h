#ifndef BINARY_H
#define BINARY_H

#include <vector>

class Binary {
public:
	Binary(int);
	int countSetBits(int);
	int hammingDistance(int, int);

private:
	int maxNumBits;
	std::vector<int> numberOfOnes;

	int inefficientCountSetBits(int);
};

#endif

