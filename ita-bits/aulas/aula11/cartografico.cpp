#include <bits/stdc++.h>
#define MAXN 1000000


using namespace std;

vector<int> graph[MAXN];
bool visited[MAXN];
int dist[MAXN];

void bfs(int source) {
	memset(dist, 0, sizeof(dist));
	memset(visited, false, sizeof(visited));
	queue<int> fila;

	fila.push(source);
	visited[source] = true;
	while (!fila.empty()) {
		vector<int>::iterator it;
		for (it = graph[fila.front()].begin(); it != graph[fila.front()].end(); it++) {
			if (!visited[*it]) {
				visited[*it] = true;
				fila.push(*it);
				dist[*it] = dist[fila.front()] + 1;
			}
		}
		fila.pop();
	}
}

int main() {
	int N, A, B;

	scanf("%d", &N);
	for (int i = 0; i < N - 1; i++) {
		scanf("%d %d", &A, &B);
		graph[A - 1].push_back(B - 1);
		graph[B - 1].push_back(A - 1);
	}

	bfs(0);
	int maxDist = 0, extreme;
	for (int i = 0; i < N; i++) if (dist[i] > maxDist) maxDist = dist[i], extreme = i;
	bfs(extreme);
	for (int i = 0; i < N; i++) maxDist = max(maxDist, dist[i]);
	printf("%d\n", maxDist);

	return 0;
}
