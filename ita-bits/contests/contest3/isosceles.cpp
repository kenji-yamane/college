#include <bits/stdc++.h>


using namespace std;

int main() {
	int N, arr[50000], topLeft[50000], topRight[50000], ans = 0;

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &arr[i]);
	
	int top = 0;
	for (int i = 0; i < N; i++)
		if (arr[i] > top)
			top++, topLeft[i] = top;
		else
			top = arr[i], topLeft[i] = top;
	top = 0;
	for (int i = N - 1; i >= 0; i--)
		if (arr[i] > top)
			top++, topRight[i] = top;
		else
			top = arr[i], topRight[i] = top;
	for (int i = 0; i < N; i++)
		ans = max(ans, min(topLeft[i], topRight[i]));
	printf("%d\n", ans);

	return 0;
}
