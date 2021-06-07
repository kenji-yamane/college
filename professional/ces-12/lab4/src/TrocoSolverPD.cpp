#include <TrocoSolver.h>

void TrocoSolverPD::solve(
	const std::vector<unsigned int> &denom,
	unsigned int value,
	std::vector<unsigned int> &coins
) {
    coins.resize(denom.size(), 0);

	std::vector<unsigned int> numCoins;
	std::vector<unsigned int> whichCoin;
	numCoins.resize(value + 1);
	whichCoin.resize(value + 1);
	for (int i = 0; i <= value; i++) {
		numCoins[i] = i;
		whichCoin[i] = 0;
		for (int j = 0; j < (int)denom.size() and denom[j] <= i; j++) {
			if (numCoins[i - denom[j]] + 1 < numCoins[i]) {
				numCoins[i] = numCoins[i - denom[j]] + 1;
				whichCoin[i] = j;
			}
		}
	}

	while (value > 0) {
		coins[whichCoin[value]]++;
		value -= denom[whichCoin[value]];
	}
}

