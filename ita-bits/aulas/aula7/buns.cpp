#include <bits/stdc++.h>


using namespace std;

int m, a[11], b[11], c[11], d[11], memo[11][1001][101];

int maxTugrik(int posic, int dough, int stuffing) {
	if (posic == m + 1) return 0;
	if (memo[posic][dough][stuffing] != -1) return memo[posic][dough][stuffing];
	int ans = 0;
	
	if (posic == 0) {
		if (dough >= c[posic])
			ans = max(ans, d[posic] + maxTugrik(posic, dough - c[posic], stuffing));
	}
	else if (stuffing >= b[posic] && dough >= c[posic])
		ans = max(ans, d[posic] + maxTugrik(posic, dough - c[posic], stuffing - b[posic]));
	if (posic < m)
		ans = max(ans, maxTugrik(posic + 1, dough, a[posic + 1]));

	return memo[posic][dough][stuffing] = ans;
}

int main() {
	int n;
	
	memset(memo, -1, sizeof(memo));
	scanf("%d %d %d %d", &n, &m, &c[0], &d[0]);
	for (int i = 1; i <= m; i++)
		scanf("%d %d %d %d", &a[i], &b[i], &c[i], &d[i]);
	printf("%d\n", maxTugrik(0, n, 0));

	return 0;
}
