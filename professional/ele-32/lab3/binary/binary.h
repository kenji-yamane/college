#ifndef BINARY_H
#define BINARY_H

#include <vector>

class Binary {
public:
	Binary(int);
	int countSetBits(int);
	int hammingDistance(int, int);
	std::vector<double> binary3ToBPSK(int);
	double binaryToBPSK(int);
	double quadraticDistance(std::vector<double>&, std::vector<double>&);

private:
	int maxNumBits;
	std::vector<int> numberOfOnes;

	int inefficientCountSetBits(int);
};

#endif

