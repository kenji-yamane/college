#include <bits/stdc++.h>


using namespace std;

int N, M, v[10000], w[10000], v2w[10000], w2v[10000], memo[10000][2];

int walk(int posic, bool path) {
	if ((path && posic == M) || (!path && posic == N)) return 0;
	if (memo[posic][path ? 1 : 0] != -1) return memo[posic][path ? 1 : 0];

	int ans = (path ? w[posic] : v[posic]) + walk(posic + 1, path);
	if (path && w2v[posic] != -1) {
		ans = max(ans, w[posic] + walk(w2v[posic] + 1, !path));
	}
	else if (!path && v2w[posic] != -1) {
		ans = max(ans, v[posic] + walk(v2w[posic] + 1, !path));
	}
	return memo[posic][path ? 1 : 0] = ans;
}

int main() {
	while (true) {
		memset(memo, -1, sizeof(memo));
		memset(v2w, -1, sizeof(v2w));
		memset(w2v, -1, sizeof(w2v));
		scanf("%d", &N);
		if (!N) break;
		for (int i = 0; i < N; i++) {
			scanf("%d", &v[i]);
		}
		scanf("%d", &M);
		for (int i = 0; i < M; i++) {
			scanf("%d", &w[i]);
		}

		for (int i = 0, j = 0; i < N && j < M; i++) {
			while (j < M && w[j] < v[i]) j++;
			if (j < M && w[j] == v[i]) w2v[j] = i, v2w[i] = j;
		}
		printf("%d\n", max(walk(0, 0), walk(0, 1)));
	}

	return 0;
}
