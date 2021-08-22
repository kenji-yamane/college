#include <TrocoSolver.h>
#include <iostream>

void TrocoSolverDivConquer::solve(
	const std::vector<unsigned int> &denom,
	unsigned int value,
	std::vector<unsigned int> &coins
) {
	int q;
	this->recursivecalls = 0;
	coins.resize(denom.size(), 0);

	this->solveRecursive(denom, value, coins, q);
}

void TrocoSolverDivConquer::solveRecursive(
	const std::vector<unsigned int> &denom,
	unsigned int value,
	std::vector<unsigned int> &coins,
	int &q
) {
	this->recursivecalls++;

	q = 0;
	if (value == 0) return;

	q = value;
	int bestCoin = 0; // 1 cent (assuming ordered input)
	for (int i = 0; i < (int)denom.size(); i++) {
		if (denom[i] > value) continue;

		int localq;
		this->solveRecursive(denom, value - denom[i], coins, localq);
		if (localq + 1 <= q) {
			q = localq + 1;
			bestCoin = i;
		}
	}

	for (auto &coin : coins) coin = 0;
	this->solveRecursive(denom, value - denom[bestCoin], coins, q);
	coins[bestCoin]++;
	q++;
}

