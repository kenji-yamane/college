#include <bits/stdc++.h>
#define inf 9999999


using namespace std;

//problema clássico de busca binária (o normal kkk)

int binarySearch(int ini, int fim, int arr[], int searched)
{
	if (ini > fim)
		return -1;

	int meio = (ini + fim)/2;

	if (searched < arr[meio])
		return binarySearch(ini, meio - 1, arr, searched);
	else if (arr[meio] < searched)
		return binarySearch(meio + 1, fim, arr, searched);
	else
		return meio;
}

int main()
{
	int N, arr[10000], M, ansi, ansj, ansdiff;

	while (scanf("%d", &N) != EOF)
	{
		ansdiff = inf;
		for (int i = 0; i < N; i++)
			scanf("%d", &arr[i]);
		sort(arr, arr + N);
		scanf("%d", &M);

		for (int i = 0; i < N; i++)
		{
			int find = binarySearch(0, N, arr, M - arr[i]);

			if (find != -1 && find != i)
			{
				if (abs(arr[find] - arr[i]) < ansdiff)
					ansi = min(arr[find], arr[i]), ansj = max(arr[find], arr[i]), ansdiff = ansj - ansi;
			}
			else if (find != -1)
				if ((i + 1 < N && arr[i + 1] == arr[i]) || (i > 0 && arr[i - 1] == arr[i]))
					ansi = ansj = arr[i], ansdiff = 0;
		}

		printf("Peter should buy books whose prices are %d and %d.\n\n", ansi, ansj);
	}

	return 0;
}
