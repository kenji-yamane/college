#include <bits/stdc++.h>


using namespace std;

int main() {
	string str;
	long long decodings[5001];

	while (true) {
		memset(decodings, 0, sizeof(decodings));
		cin >> str;
		if (str[0] != '0') {
			decodings[0] = 1;
		}
		if (str.size() > 1 && (str[0] == '1' || (str[0] == '2' && str[1] < '7'))) {
			decodings[1] = 1;
		}
		if (str == "0") break;
		for (int i = 1; i < (int)str.size(); i++) {
			if (str[i] != '0') {
				decodings[i] += decodings[i - 1];
			}
			if (i + 1 < (int)str.size() && (str[i] == '1' || (str[i] == '2' && str[i + 1] < '7'))) {
				decodings[i + 1] += decodings[i - 1];
			}
		}
		printf("%lld\n", decodings[str.size() - 1]);
	}

	return 0;
}
