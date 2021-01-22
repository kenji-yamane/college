#include <bits/stdc++.h>


using namespace std;

vector<int> graph[10000], reversed[10000];
bool visited[10000], connected = true;

void dfs(int source, vector<int> gr[]) {
	visited[source] = true;

	for (vector<int>::iterator it = gr[source].begin(); it != gr[source].end(); it++) {
		if (!visited[*it]) {
			dfs(*it, gr);
		}
	}
}

int main() {
	int N, A, B;

	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &A, &B);
		graph[A - 1].push_back(B - 1);
		reversed[B - 1].push_back(A - 1);
	}

	dfs(0, graph);
	for (int i = 0; i < N; i++) if (!visited[i]) connected = false;;
	memset(visited, false, sizeof(visited));
	dfs(0, reversed);
	for (int i = 0; i < N; i++) if (!visited[i]) connected = false;
	printf("%c\n", connected == true ? 'S' : 'N');

	return 0;
}
