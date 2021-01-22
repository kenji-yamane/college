#include <bits/stdc++.h>


using namespace std;

int main() {
	int N, arr[100000], love, x, y;

	while (scanf("%d", &N) != EOF) {
		x = y = love = 0;

		if (!N) break;
		for (int i = 0; i < N; i++) {
			scanf("%d", &arr[i]);
			love ^= arr[i];
		}
		if (N == 1) {
			printf("%d\n", love);
			continue;
		}
		
		int separator = love&(-love);
		for (int i = 0; i < N; i++) {
			if (arr[i]&separator) {
				x ^= arr[i];
			}
			else {
				y ^= arr[i];
			}
		}
		printf("%d %d\n", min(x, y), max(x, y));
	}

	while (scanf("%d", &N) != EOF);

	return 0;
}
