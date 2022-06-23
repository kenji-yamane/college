#ifndef BINARY_H
#define BINARY_H

#include <vector>
#include <map>

class Binary {
public:
	Binary(int);

	int countSetBits(int);
	int hammingDistance(int, int);

	std::vector<double> binary3ToBPSK(int);
	double binaryToBPSK(int);
	double quadraticDistance(std::vector<double>&, std::vector<double>&);

	void populateLogprob(double p);
	double logprob(int, int);

private:
	int maxNumBits;
	std::vector<int> numberOfOnes;
	std::vector<double> logprobDistance;

	int inefficientCountSetBits(int);
	double inefficientLogprob(int, int, double);
};

#endif

