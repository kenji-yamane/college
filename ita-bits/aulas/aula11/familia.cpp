#include <bits/stdc++.h>


using namespace std;

vector<int> graph[10001];
int generations[10001], dist[10001], maxDist;
bool visited[10001];

void bfs(int source) {
	queue<int> fila;
	visited[source] = true;
	dist[source] = 0;

	fila.push(source);
	while (!fila.empty()) {
		vector<int>::iterator it;
		for (it = graph[fila.front()].begin(); it != graph[fila.front()].end(); it++) {
			if (!visited[*it]) {
				fila.push(*it);
				visited[*it] = true;
				dist[*it] = dist[fila.front()] + 1;
				if (dist[*it] > maxDist) maxDist = dist[*it];
			}
		}
		fila.pop();
	}
	maxDist++;
}

int main() {
	int N, M, aux, party[10001] = {};

	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++) {
		scanf("%d", &aux);
		graph[aux].push_back(i + 1);
		graph[i + 1].push_back(aux);
	}
	bfs(0);
	for (int i = 0; i <= N; i++) {
		generations[dist[i]]++;
	}
	for (int i = 0; i < M; i++) {
		scanf("%d", &aux);
		party[dist[aux]]++;
	}
	for (int i = 1; i < maxDist; i++) {
		printf("%.2lf", (double)100*party[i]/generations[i]);
		printf("%c", i == maxDist - 1 ? '\n' : ' ');
	}

	return 0;
}
