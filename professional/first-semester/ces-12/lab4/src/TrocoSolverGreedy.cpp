#include <TrocoSolver.h>

void TrocoSolverGreedy::solve(
	const std::vector<unsigned int> &denom,
	unsigned int value,
	std::vector<unsigned int> &coins
) {
	coins.resize(denom.size(), 0);
	for (int i = (int)denom.size() - 1; i >= 0 && value > 0; i--) {
		coins[i] = value/denom[i];
		value = value%denom[i];
	}
}

