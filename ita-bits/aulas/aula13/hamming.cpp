#include <bits/stdc++.h>


using namespace std;

int main() {
	int ans;
	unsigned long long x, y, z;

	while (true) {
		scanf("%llu %llu", &x, &y);
		if (!x && !y) break;

		ans = 0;
		z = x^y;
		while (z > 0) {
			ans++;
			z = z - (z&(-z));
		}
		printf("%d\n", ans);
	}

	return 0;
}
