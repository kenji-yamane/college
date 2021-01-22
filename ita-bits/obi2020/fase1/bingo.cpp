#include <bits/stdc++.h>


using namespace std;


int main() {
	int N, K, U, aux, sorted[10000], marked[1000] = {};
	queue<int> indexes[10001];
	vector<int> winners;
	bool over = false;

	scanf("%d %d %d", &N, &K, &U);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < K; j++) {
			scanf("%d", &aux);
			indexes[aux].push(i);
		}
	}
	for (int i = 0; i < U; i++) scanf("%d", &sorted[i]);
	for (int i = 0; !over; i++) {
		while (!indexes[sorted[i]].empty()) {
			marked[indexes[sorted[i]].front()]++;
			if (marked[indexes[sorted[i]].front()] == K) {
				over = true;
				winners.push_back(indexes[sorted[i]].front());
			}
			indexes[sorted[i]].pop();
		}
	}
	sort(winners.begin(), winners.end());
	for (int i = 0; i < (int)winners.size(); i++) {
		printf("%d%c", winners[i] + 1, i == (int)winners.size() - 1 ? '\n' : ' ');
	}

	return 0;
}
