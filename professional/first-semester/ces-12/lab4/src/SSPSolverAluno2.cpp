#include <SubsetSumSolver.h>
#include <Subset.h>
#include <algorithm>
#include <iostream>

std::vector<Subset> SSPSolverAluno2::subsets;
std::vector<long> SSPSolverAluno2::weigths;
std::vector<char> SSPSolverAluno2::indexes;

void SSPSolverAluno2::reset(std::vector<long> &input) {
	this->weigths = input;
	this->subsets.clear();
}

void SSPSolverAluno2::collectSums(size_t posic, long sum) {
	if (posic == this->weigths.size()) {
		this->subsets.push_back({sum, this->indexes});
		return;
	}

	this->indexes.push_back(true);
	this->collectSums(posic + 1, sum + this->weigths[posic]);
	this->indexes.pop_back();

	this->indexes.push_back(false);
	this->collectSums(posic + 1, sum);
	this->indexes.pop_back();
}

/// Aluno2: segunda solucao do aluno = Meet-in-the-Middle OU Branch & Bound
bool SSPSolverAluno2::solve(
	const std::vector<long> &input,
	long value,
	std::vector<char> &output
) {
	std::vector<long> firstHalf, secondHalf;
	std::vector<Subset> firstHalfSubsets, secondHalfSubsets;

	for (long i = 0; i < input.size(); i++) {
		if (i < input.size()/2) firstHalf.push_back(input[i]);
		else                    secondHalf.push_back(input[i]);
	}

	this->reset(firstHalf);
	this->collectSums(0, 0);
	std::sort(this->subsets.begin(), this->subsets.end(), sortSubsets);
	firstHalfSubsets = this->subsets;

	this->reset(secondHalf);
	this->collectSums(0, 0);
	secondHalfSubsets = this->subsets;

	for (auto const &subset : secondHalfSubsets) {
		long ini = 0, fin = (long)firstHalfSubsets.size(), searched = value - subset.sum;

		while (ini <= fin) {
			long middle = (ini + fin)/2;

			if (searched < firstHalfSubsets[middle].sum) {
				fin = middle - 1;
			} else if (searched > firstHalfSubsets[middle].sum) {
				ini = middle + 1;
			} else {
				std::vector<char> &firstOutput = firstHalfSubsets[middle].indexes;

				output.clear();
				output.insert(output.end(), firstOutput.begin(), firstOutput.end());
				output.insert(output.end(), subset.indexes.begin(), subset.indexes.end());
				return true;
			}
		}
	}

	return false;
}

