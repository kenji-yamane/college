#include <bits/stdc++.h>


using namespace std;

int N, grid[100][100];
bool visited[100][100];

void dfs(int i, int j) {
	if (visited[i][j]) return;
	visited[i][j] = true;
	if (i < N - 1 && grid[i + 1][j] >= grid[i][j]) dfs(i + 1, j);
	if (j < N - 1 && grid[i][j + 1] >= grid[i][j]) dfs(i, j + 1);
	if (i > 0 && grid[i - 1][j] >= grid[i][j]) dfs(i - 1, j);
	if (j > 0 && grid[i][j - 1] >= grid[i][j]) dfs(i, j - 1);
}

int main() {
	int I, J, ans = 0;

	scanf("%d %d %d", &N, &I, &J);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &grid[i][j]);
		}
	}

	dfs(I - 1, J - 1);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (visited[i][j]) ans++;
		}
	}
	printf("%d\n", ans);

	return 0;
}
