#include <bits/stdc++.h>


using namespace std;

int main() {
	int N, C, P, I, X, parents[1000];
	set<int> s;
	memset(parents, -1, sizeof(parents));

	scanf("%d %d", &N, &C);
	for (int i = 0; i < C; i++) {
		scanf("%d %d", &P, &I);
		for (int j = 0; j < I; j++) {
			scanf("%d", &X);
			parents[X - 1] = P - 1;
		}
	}
	
	for (int i = 0; i < N; i++) {
		int j = i;
		while (parents[j] != -1) {
			j = parents[j];
		}
		s.insert(j);
	}
	for (set<int>::iterator it = s.begin(); it != s.end(); it++) {
		printf("%d\n", *it + 1);
	}

	return 0;
}
