#include "hashfunctions.h"

int hashdiv(std::string str, int m ) {
	int ans = 0;

	for (const auto &c : str) {
		ans += (int)c;
	}

	return ans%m;
}//hashdiv

int hashdiv29(std::string str) {
    return hashdiv(str,29);
}


