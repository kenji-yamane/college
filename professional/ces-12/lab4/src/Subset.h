#ifndef SUBSET
#define SUBSET

#include <vector>

class Subset {
public:
	Subset();
	Subset(long sum, std::vector<char> indexes);
	long sum;
	std::vector<char> indexes;
};

bool sortSubsets(const Subset &a, const Subset &b);

#endif

