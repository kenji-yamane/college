#include <bits/stdc++.h>


using namespace std;

int main() {
	int N, M, K, arr[1000];

	while (scanf("%d %d %d", &N, &M, &K) != EOF) {
		for (int i = 0; i < N; i++) {
			scanf("%d", &arr[i]);
		}
		printf("%d\n", arr[(K - 1 - M%N + N)%N]);
	}

	return 0;
}
