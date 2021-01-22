#include <bits/stdc++.h>


using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	string aux;
	long long dp[27][27], ans = 0;
	memset(dp, 0, sizeof(dp));

	cin >> aux;
	for (int i = 0; i < (int)aux.size(); i++) {
		for (int j = 1; j < 27; j++) {
			dp[aux[i] - 'a' + 1][j] += dp[j][0];
		}
		dp[aux[i] - 'a' + 1][0]++;
	}
	for (int i = 0; i < 27; i++) {
		for (int j = 0; j < 27; j++) {
			ans = max(ans, dp[i][j]);
		}
	}
	printf("%lld\n", ans);

	return 0;
}
