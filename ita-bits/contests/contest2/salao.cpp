#include <bits/stdc++.h>
#define inf 99999999


using namespace std;

//guloso

int counting[100000];

int fillFloor(int qtd, int sumNeeded)
{
	int keep[100000], wood = 0;
	for (int i = 0; i <= sumNeeded; i++)
		keep[i] = counting[i];

	while (keep[sumNeeded] > 0 && qtd > 0)
		wood++, keep[sumNeeded]--, qtd--;
	
	for (int i = 1; i < sumNeeded && qtd > 0; i++)
		if (i != sumNeeded - i)
			while (keep[i] > 0 && keep[sumNeeded - i] > 0 && qtd > 0)
				keep[i]--, keep[sumNeeded - i]--, qtd--, wood += 2;
		else
			while (keep[i] > 1 && qtd > 0)
				keep[i] -= 2, wood += 2, qtd--;
	
	return qtd == 0 ? wood : inf;
}

int main()
{
	int N, M, L, K, ans, aux;

	while (true)
	{
		ans = inf;
		memset(counting, 0, sizeof(counting));
		scanf("%d %d", &N, &M);
		if (!N && !M) break;
		scanf("%d %d", &L, &K);
		for (int i = 0; i < K; i++)
			scanf("%d", &aux), counting[aux]++;
		
		if (100*N%L == 0)
			ans = min(ans, fillFloor(100*N/L, M));
		if (100*M%L == 0)
			ans = min(ans, fillFloor(100*M/L, N));

		if (ans == inf)
			printf("impossivel\n");
		else
			printf("%d\n", ans);
	}

	return 0;
}
