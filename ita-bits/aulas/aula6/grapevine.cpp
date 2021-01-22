#include <bits/stdc++.h>


using namespace std;

//essas duas primeiras funções levemente parecidas com busca binária

int mtx[500][500];

int upperBound(int line, int ini, int fim, int num)
{
	if (ini == fim) return ini;
	int meio = (ini + fim)/2 + 1;

	if (mtx[line][meio] <= num)
		return upperBound(line, meio, fim, num);
	else
		return upperBound(line, ini, meio - 1, num);
}

int lowerBound(int line, int ini, int fim, int num)
{
	if (ini == fim) return ini;
	int meio = (ini + fim)/2;

	if (mtx[line][meio] >= num)
		return lowerBound(line, ini, meio, num);
	else
		return lowerBound(line, meio + 1, fim, num);
}

int main()
{
	int N, M, Q, L, U, bounds[500][2];

	while (true)
	{
		scanf("%d %d", &N, &M);
		if (!N && !M) break;

		for (int i = 0; i < N; i++)
			for (int j = 0; j < M; j++)
				scanf("%d", &mtx[i][j]);
		scanf("%d", &Q);
		for (int i = 0; i < Q; i++)
		{
			scanf("%d %d", &L, &U);
			for (int i = 0; i < N; i++)
			{
				bounds[i][0] = lowerBound(i, 0, M - 1, L);
				bounds[i][1] = upperBound(i, 0, M - 1, U);
			}
			
			int ans = 0;
			for (int i = 0; i < N; i++)
			{
				while (i + ans < N && bounds[i][0] + ans <= bounds[i + ans][1])
					if (mtx[i][bounds[i][0]] < L || mtx[i + ans][bounds[i + ans][1]] > U)
						break;
					else
						ans++;
			}
			printf("%d\n", ans);
		}
		printf("-\n");
	}

	return 0;
}
