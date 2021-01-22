#include <cstdio>
#include <algorithm>


using namespace std;

int arr[100000];

int binarySearch(int ini, int fim, int searched)
{
	if (ini > fim) return -1;
	int meio = (ini + fim)/2;
	
	if (searched < arr[meio])
		return binarySearch(ini, meio - 1, searched);
	else if (arr[meio] < searched)
		return binarySearch(meio + 1, fim, searched);
	else
		return meio;
}

int main()
{
	int N, K, i;
	
	scanf("%d", &N);
	for (i = 0; i < N; i++)
		scanf("%d", &arr[i]);
	scanf("%d", &K);

	i = 0;
	while (binarySearch(0, N, K - arr[i]) == -1)
		i++;
	printf("%d %d\n", min(K - arr[i], arr[i]), max(K - arr[i], arr[i]));
	
	return 0;
}
