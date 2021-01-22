#include <bits/stdc++.h>
#define MAXN 10000


using namespace std;

vector<int> graph[MAXN];
bool visited[MAXN];
int dist[MAXN];

void dfs(int source) {
	visited[source] = true;

	vector<int>::iterator it;
	for (it = graph[source].begin(); it != graph[source].end(); it++) {
		if (!visited[*it]) {
			dist[*it] = dist[source] + 1;
			dfs(*it);
		}
	}
}

int main() {
	int N, A, B, X, Y;

	scanf("%d %d %d", &N, &A, &B);
	for (int i = 0; i < N - 1; i++) {
		scanf("%d %d", &X, &Y);
		graph[X - 1].push_back(Y - 1);
		graph[Y - 1].push_back(X - 1);
	}
	dfs(A - 1);
	printf("%d\n", dist[B - 1]);

	return 0;
}
