#include <bits/stdc++.h>


using namespace std;

vector<vector<int> > candies;
int N, M, memo[1000000][2], aux;

int diabetes(int state, int acted) {
	if (state >= N*M) return 0;
	if (memo[state][acted] != -1) return memo[state][acted];
	int i = (state - state%M)/M, j = state%M, ans = 0;

	// Escolho essa caixa
	if (j >= M - 2)
		ans = max(ans, candies[i][j] + diabetes((i + 2)*M, 0));
	else
		ans = max(ans, candies[i][j] + diabetes(i*M + j + 2, 1));

	// Ou não escolho
	if (j == M - 1) {
		ans = max(ans, diabetes(acted == 1 ? (i + 2)*M : (i + 1)*M, 0));
	}
	else {
		ans = max(ans, diabetes(i*M + j + 1, acted));
	}

	return memo[state][acted] = ans;
}

int main() {
	while (true) {
		memset(memo, -1, sizeof(memo));
		scanf("%d %d", &N, &M);
		if (!N && !M) break;

		for (int i = 0; i < N; i++) {
			vector<int> v;
			for (int j = 0; j < M; j++) {
				scanf("%d", &aux);
				v.push_back(aux);
			}
			candies.push_back(v);
		}
		printf("%d\n", diabetes(0, 0));

		candies.clear();
	}

	return 0;
}
