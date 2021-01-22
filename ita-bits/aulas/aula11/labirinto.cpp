#include <bits/stdc++.h>
#define inf 1000000


using namespace std;

int N, M, grid[50][50], dist[50][50];
queue<pair<int, int> > fila;

int cost(int xfrom, int yfrom, int xto, int yto, int turn) {
	int heightFrom = (grid[xfrom][yfrom] + turn)%10;
	int heightTo = (grid[xto][yto] + turn)%10;

	if (heightTo < heightFrom + 2) return 1;
	else return (10 - heightTo + 1);
}

void bfs(int x, int y) {
	for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) dist[i][j] = inf;
	dist[x][y] = 0;
	fila.push(make_pair(x, y));

	while (!fila.empty()) {
		x = fila.front().first;
		y = fila.front().second;

		if (x < N - 1 && cost(x, y, x + 1, y, dist[x][y]) + dist[x][y] < dist[x + 1][y]) {
			dist[x + 1][y] = cost(x, y, x + 1, y, dist[x][y]) + dist[x][y];
			fila.push(make_pair(x + 1, y));
		}
		if (x > 0 && cost(x, y, x - 1, y, dist[x][y]) + dist[x][y] < dist[x - 1][y]) {
			dist[x - 1][y] = cost(x, y, x - 1, y, dist[x][y]) + dist[x][y];
			fila.push(make_pair(x - 1, y));
		}
		if (y < M - 1 && cost(x, y, x, y + 1, dist[x][y]) + dist[x][y] < dist[x][y + 1]) {
			dist[x][y + 1] = cost(x, y, x, y + 1, dist[x][y]) + dist[x][y];
			fila.push(make_pair(x, y + 1));
		}
		if (y > 0 && cost(x, y, x, y - 1, dist[x][y]) + dist[x][y] < dist[x][y - 1]) {
			dist[x][y - 1] = cost(x, y, x, y - 1, dist[x][y]) + dist[x][y];
			fila.push(make_pair(x, y - 1));
		}

		fila.pop();
	}
}

int main() {
	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%d", &grid[i][j]);
		}
	}
	bfs(0, 0);
	printf("%d\n", dist[N - 1][M - 1]);

	return 0;
}
