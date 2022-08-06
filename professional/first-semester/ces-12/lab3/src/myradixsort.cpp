
#include <mysortfunctions.h>
#include <queue>

void myradixsort(std::vector<int> &v, SortStats &stats) {
	stats.recursive_calls = stats.depth_recursion_stack = 1;

	std::queue<int> divisors[32];

	int biggest = 0;
	for (const auto &c : v) biggest = std::max(biggest, c);

	int reversal = 0;
	for (int mask = 31; mask < biggest or (mask & biggest) != 0; mask <<= 5) {
		for (const auto &c : v) {
			divisors[(c & mask) >> reversal].push(c);
		}

		int aux = 0;
		for (int i = 0; i < 32; i++) while (!divisors[i].empty()) {
			v[aux++] = divisors[i].front();
			divisors[i].pop();
		}

		reversal += 5;
	}
}
