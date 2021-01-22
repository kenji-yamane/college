#include <bits/stdc++.h>


using namespace std;

int N, M;
char grid[500][500];

void rain(int i, int j)
{
	grid[i][j] = 'o';
	if (i + 1 < N && grid[i + 1][j] == '.')
		rain(i + 1, j);
	else if (i + 1 < N && grid[i + 1][j] == '#')
	{
		if (j + 1 < M && grid[i][j + 1] == '.')
			rain(i, j + 1);
		if (j > 0 && grid[i][j - 1] == '.')
			rain(i, j - 1);
	}
}

int main()
{
	int leak;

	scanf("%d %d", &N, &M);
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
		{
			scanf(" %c", &grid[i][j]);
			if (grid[i][j] == 'o')
				leak = j;
		}
	
	rain(0, leak);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			printf("%c", grid[i][j]);
		printf("\n");
	}

	return 0;
}
