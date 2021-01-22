#include <bits/stdc++.h>


using namespace std;

//guloso

int main()
{
	int N, M, i, arr[1000], ans = 0;
	
	scanf("%d %d", &N, &M);
	for (i = 0; i < N; i++)
		scanf("%d", &arr[i]);
	
	for (i = 0; i < N - 1; i++)
		ans += abs(arr[i] - M), arr[i + 1] += M - arr[i], arr[i] += M - arr[i];
	printf("%d\n", ans);
	
	return 0;
}
