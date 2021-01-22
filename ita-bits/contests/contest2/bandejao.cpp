#include <bits/stdc++.h>


using namespace std;

//guloso no pedaço da fila com o qual vc sumiu

int main()
{
	int N, K, arr[1000] = {}, diff[1000], ans, ctrl;

	while (scanf("%d %d", &N, &K) != EOF)
	{
		for (int i = 1; i < N; i++)
			scanf("%d", &arr[i]);
		for (int i = 0; i < N - 1; i++)
			diff[i] = arr[i + 1] - arr[i];
		sort(diff, diff + N - 1, greater<int>());
		
		ans = arr[N - 1];
		ctrl = 0;
		while (K > 1)
			ans -= diff[ctrl++], K--;
		printf("%d\n", ans);
	}

	return 0;
}
