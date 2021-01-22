#include <bits/stdc++.h>


using namespace std;

int main() {
	int N;
	long long int x, aux;

	while (true) {
		x = 0;
		scanf("%d", &N);
		if (!N) break;

		for (int i = 0; i < N; i++) {
			scanf("%lld", &aux);
			x ^= aux;
		}

		printf("%lld\n", x);
	}

	return 0;
}
