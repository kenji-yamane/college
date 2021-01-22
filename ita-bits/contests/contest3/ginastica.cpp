#include <bits/stdc++.h>
#define mod 1000000007


using namespace std;

int M, N, memo[51][100001];

int program(int minutes, int value) {
	if (memo[minutes][value] != -1) return memo[minutes][value];
	if (minutes == 1) return 1;
	int ans = 0;

	if (value > M) ans = (ans + program(minutes - 1, value - 1))%mod;
	if (value < N) ans = (ans + program(minutes - 1, value + 1))%mod;
	
	return memo[minutes][value] = ans;
}

int main() {
	int T, ans = 0;

	memset(memo, -1, sizeof(memo));
	scanf("%d %d %d", &T, &M, &N);
	for (int i = M; i <= N; i++) {
		ans = (ans + program(T, i))%mod;
	}
	printf("%d\n", ans);

	return 0;
}
