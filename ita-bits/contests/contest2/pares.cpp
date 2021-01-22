#include <bits/stdc++.h>


using namespace std;

//Força bruta

int main()
{
	int N, I, F, arr[1000], ans = 0;

	scanf("%d %d %d", &N, &I, &F);
	for (int i = 0; i < N; i++)
		scanf("%d", &arr[i]);

	for (int i = 0; i < N; i++)
		for (int j = i + 1; j < N; j++)
			if (arr[i] + arr[j] >= I && arr[i] + arr[j] <= F)
				ans++;
	printf("%d\n", ans);

	return 0;
}
