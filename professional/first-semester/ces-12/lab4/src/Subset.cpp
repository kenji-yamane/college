#include <Subset.h>

Subset::Subset(long sum, std::vector<char> indexes) : sum(sum), indexes(indexes) {
}

Subset::Subset() : sum(0) {
}

bool sortSubsets(const Subset &a, const Subset &b) {
	return (a.sum < b.sum);
}

