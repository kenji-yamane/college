#include <bits/stdc++.h>


using namespace std;

int n, m, costs[20][21], ratings[20][20], memo[20][21][1001];

int power(int batch, int weapon, int money) {
	if (batch == n) return 0;
	if (weapon == m + 1) return power(batch + 1, 0, money);
	if (memo[batch][weapon][money] != -1) return memo[batch][weapon][money];
	int ans = power(batch + 1, 0, money);

	if (weapon == 0 && money >= costs[batch][0]) {
		ans = max(ans, power(batch, 1, money - costs[batch][0]));
	}
	if (weapon > 0 && money >= costs[batch][weapon]) {
		ans = max(ans, ratings[batch][weapon - 1] + power(batch, weapon, money - costs[batch][weapon]));
	}
	if (weapon > 0) {
		ans = max(ans, power(batch, weapon + 1, money));
	}

	return memo[batch][weapon][money] = ans;
}

int main() {
	int T, k;

	scanf("%d", &T);
	while (T--) {
		memset(memo, -1, sizeof(memo));
		scanf("%d %d %d", &n, &m, &k);
		for (int i = 0; i < n; i++)
			scanf("%d", &costs[i][0]);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &costs[i][j + 1]);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &ratings[i][j]);

		printf("%d\n", power(0, 0, k));
	}

	return 0;
}
