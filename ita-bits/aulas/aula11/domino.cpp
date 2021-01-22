#include <bits/stdc++.h>


using namespace std;

int graph[7][7];
bool visited[7], connected;

void dfs(int source) {
	visited[source] = true;

	for (int i = 0; i < 7; i++) {
		if (!visited[i] && graph[source][i] > 0) {
			dfs(i);
		}
	}
}

int main() {
	int N, X, Y, degrees[7], odd, test = 0;

	while (true) {
		odd = 0;
		memset(graph, 0, sizeof(graph));
		memset(degrees, 0, sizeof(degrees));
		memset(visited, false, sizeof(visited));

		scanf("%d", &N);
		if (!N) break;
		for (int i = 0; i < N; i++) {
			scanf("%d %d", &X, &Y);
			degrees[X]++;
			degrees[Y]++;
			graph[X][Y] = 1;
			graph[Y][X] = 1;
		}
		for (int i = 0; i < 7; i++) if (degrees[i]%2) odd++;

		connected = true;
		dfs(X);
		for (int i = 0; i < 7; i++) if (!visited[i] && degrees[i]) connected = false;
		bool eulerian = false;
		if (connected && (odd == 2 || odd == 0)) eulerian = true;
		printf("Teste %d\n", ++test);
		printf("%s\n\n", (eulerian ? "sim" : "nao"));
	}

	return 0;
}
