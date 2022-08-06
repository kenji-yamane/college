#include <SubsetSumSolver.h>

#define UNKNOWN -1
#define ORIGIN -2

bool SSPSolverPD::solve(
	const std::vector<long> &input,
    long value,
	std::vector<char> &output
) {
    output.resize(input.size());
	std::vector<std::vector<long> > dpTable(input.size() + 1, std::vector<long>(value + 1, UNKNOWN));

	dpTable[0][0] = ORIGIN;
	for (long i = 0; i < (long)dpTable.size() - 1; i++) {
		for (long j = 0; j < (long)dpTable[i].size(); j++) {
			if (dpTable[i][j] != UNKNOWN) {
				// chooses not to include ith input, so its ancestor doesn't change
				dpTable[i + 1][j] = dpTable[i][j];

				// chooses to include ith input, so its ancestor is (i, j)
				if (j + input[i] <= value) {
					dpTable[i + 1][j + input[i]] = i*(value + 1) + j;
				}
			}
		}
	}

	if (dpTable[input.size()][value] == UNKNOWN) {
		return false;
	} else {
		long i = (long)input.size(), j = value;
		while (dpTable[i][j] != ORIGIN) {
			long ancestor = dpTable[i][j];

			// recovering ancestor
			j = ancestor%(value + 1);
			i = (ancestor - j)/(value + 1);
			output[i] = true;
		}
		return true;
	}
}
