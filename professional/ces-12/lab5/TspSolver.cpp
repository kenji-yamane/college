#include <TspSolver.h>
#include <algorithm>
#include <queue>

bool PrimRule::operator()(Edge const &e1, Edge const &e2) {
	if (e1.weigth != e2.weigth) {
		return e2.weigth < e1.weigth;
	} else if (e1.origin != e2.origin) {
		return e2.origin < e1.origin;
	} else {
		return e2.destination < e1.destination;
	}
}

bool PreorderRule(Edge &e1, Edge &e2) {
	if (e1.weigth != e2.weigth) {
		return e1.weigth < e2.weigth;
	} else {
		return e1.destination < e2.destination;
	}
}

void TspSolver::solve(TspReader &tr,std::vector<int> &percourse) {
	City c;
	std::vector<City> vertexes;
	while (tr.getCities(c)) {
		vertexes.push_back(c);
	}

	std::vector<std::vector<int> > graph(vertexes.size(), std::vector<int>(vertexes.size(), 0));
	for (int i = 0; i < (int)vertexes.size(); i++) {
		for (int j = 0; j < (int)vertexes.size(); j++) {
			if (i != j) {
				graph[i][j] = vertexes[i].disti(vertexes[j]);
			}
		}
	}

	std::vector<std::vector<Edge> > primTree;
	Prim(graph, primTree);
	for (int i = 0; i < primTree.size(); i++) {
		std::sort(primTree[i].begin(), primTree[i].end(), PreorderRule);
	}
	std::vector<bool> visited(vertexes.size(), false);
	Preorder(primTree, 0, percourse, visited);
}//solve

// Prim receives a graph in adjacency matrix form and returns the resulting
// minimum spanning tree in the form of an adjacency list
void Prim(const std::vector<std::vector<int> > &graph, std::vector<std::vector<Edge> > &T) {
	int vNum = (int)graph[0].size();
	std::priority_queue<Edge, std::vector<Edge>, PrimRule> pq;
	
	T.resize(vNum);
	std::vector<bool> visited(vNum, false);
	int vertex = 0;
	visited[0] = true;
	for (int i = 0; i < vNum - 1; i++) {
		for (int j = 0; j < (int)graph[vertex].size(); j++) {
			if (j != vertex and not visited[j]) {
				pq.push(Edge{vertex, j, graph[vertex][j]});
			}
		}
		while (visited[pq.top().destination] and not pq.empty()) {
			pq.pop();
		}
		if (not pq.empty()) {
			Edge e = pq.top();
			vertex = e.destination;
			visited[e.destination] = true;
			T[e.origin].push_back(Edge{e.origin, e.destination, e.weigth});
			T[e.destination].push_back(Edge{e.destination, e.origin, e.weigth});
			pq.pop();
		}
		while (visited[pq.top().destination] and not pq.empty()) {
			pq.pop();
		}
	}
}

void Preorder(std::vector<std::vector<Edge> > &T, int vertex, std::vector<int> &ans, std::vector<bool> &visited) {
	visited[vertex] = true;
	ans.push_back(vertex + 1);
	for (int i = 0; i < T[vertex].size(); i++) {
		if (not visited[T[vertex][i].destination]) {
			Preorder(T, T[vertex][i].destination, ans, visited);
		}
	}
}

