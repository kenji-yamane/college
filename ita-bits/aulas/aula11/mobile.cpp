#include <bits/stdc++.h>
#define MAXN 10001


using namespace std;

vector<int> graph[MAXN];
bool visited[MAXN], balanced = true;

int dfs(int source) {
	visited[source] = true;
	int sons = 0, cte = -1;

	vector<int>::iterator it;
	for (it = graph[source].begin(); it != graph[source].end(); it++) {
		if (!visited[*it]) {
			int son = dfs(*it);
			if (cte == -1) cte = son;
			else if (cte != son) balanced = false;
			sons += son;
		}
	}

	return sons + 1;
}

int main() {
	int N, X, Y;

	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &X, &Y);
		graph[X].push_back(Y);
		graph[Y].push_back(X);
	}
	dfs(0);
	printf("%s\n", balanced ? "bem" : "mal");

	return 0;
}
