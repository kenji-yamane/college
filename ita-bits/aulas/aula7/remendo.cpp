#include <bits/stdc++.h>


using namespace std;

int circularDiff(int a, int b, int N) {
	if (b - a >= 0) {
		return b - a;
	}
	else {
		return b - a + N;
	}
}

int N, C, T1, T2, holes[1000];

int optimal(int start, int posic) {
	
	int i, t1, t2;
	for (i = posic; i < start and circularDiff(holes[i], holes[posic]) > max(T1, T2); i = (i + 1)%N) {
		if (circularDiff(holes[i], holes[posic]) > min(T1, T2)) {
			t1 = 
		}
	}
}

int main() {
	while (scanf("%d %d %d %d", &N, &C, &T1, &T2) != EOF) {
		for (int i = 0; i < N; i++) {
			scanf("%d", &holes[i]);
		}
	}

	return 0;
}
