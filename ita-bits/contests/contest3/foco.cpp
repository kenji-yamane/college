#include <bits/stdc++.h>


using namespace std;

bool compare_interval(pair<int, int> &a, pair<int, int> &b) {
	if (a.first != b.first) {
		return (a.first < b.first);
	}
	else {
		return (a.second < b.second);
	}
}

int main() {
	int N, i;

	while (scanf("%d", &N) != EOF) {
		pair<int, int> intervals[1000000];
		int focus = 0, limiter = -1;

		for (i = 0; i < N; i++) {
			scanf("%d %d", &intervals[i].first, &intervals[i].second);
		}

		sort(intervals, intervals + N, compare_interval);
		for (i = 0; i < N; i++) {
			limiter = min(limiter, intervals[i].second);
			if (intervals[i].first > limiter) {
				focus++;
				limiter = intervals[i].second;
			}
		}
		printf("%d\n", focus);
	}

	return 0;
}
