#include <bits/stdc++.h>


using namespace std;

vector<int> graph[1000];
bool visited[1000], connected = true;

void dfs(int source) {
	visited[source] = true;

	for (vector<int>::iterator it = graph[source].begin(); it != graph[source].end(); it++) {
		if (!visited[*it]) {
			dfs(*it);
		}
	}
}

int main() {
	int N, D;
	pair<int, int> coord[1000];

	scanf("%d %d", &N, &D);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &coord[i].first, &coord[i].second);
	}
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			int dxx = pow(coord[i].first - coord[j].first, 2);
			int dyy = pow(coord[i].second - coord[j].second, 2);
			if (D*D >= dxx + dyy) {
				graph[i].push_back(j);
				graph[j].push_back(i);
			}
		}
	}

	dfs(0);
	for (int i = 0; i < N; i++) if (!visited[i]) connected = false;
	printf("%c\n", connected ? 'S' : 'N');

	return 0;
}
