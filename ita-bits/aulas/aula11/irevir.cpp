#include<bits/stdc++.h>


using namespace std;

vector<int> graph[2000], reversed[2000];
bool rev, connected, visited[2000];

void dfs(int source) {
	visited[source] = true;

	for (auto it : (rev == false ? graph[source] : reversed[source])) {
		if (!visited[it]) {
			dfs(it);
		}
	}
}

int main() {
	int N, M, V, W, P;

	while (true) {
		scanf("%d", &N);
		if (!N) break;
		scanf("%d", &M);

		for (int i = 0; i < M; i++) {
			scanf("%d %d %d", &V, &W, &P);
			graph[V - 1].push_back(W - 1);
			reversed[W - 1].push_back(V - 1);
			if (P == 2) graph[W - 1].push_back(V - 1), reversed[V - 1].push_back(W - 1);
		}

		rev = false;
		dfs(0);
		connected = true;
		for (int i = 0; i < N; i++) if (!visited[i]) connected = false;
		memset(visited, false, sizeof(visited));
		rev = true;
		dfs(0);
		for (int i = 0; i < N; i++) if (!visited[i]) connected = false;
		printf("%d\n", connected == false ? 0 : 1);
		
		for (int i = 0; i < N; i++) graph[i].clear();
		for (int i = 0; i < N; i++) reversed[i].clear();
		memset(visited, false, sizeof(visited));
	}

	return 0;
}
