#include <bits/stdc++.h>
#define inf 1000000000


using namespace std;

//Binary Search The Answer

int N, C, T, arr[100000];

bool simulation(int time)
{
	int acc = 0, competitors = 1;
	for (int i = 0; i < N; i++)
	{
		if (acc == 0 && arr[i]/T + (arr[i]%T == 0 ? 0 : 1) > time)
			return false;
		else if ((acc + arr[i])/T + ((acc + arr[i])%T == 0 ? 0 : 1) <= time)
			acc += arr[i];
		else
			acc = 0, competitors++, i--;
	}
	
	return (competitors <= C);
}

int main()
{
	scanf("%d %d %d", &N, &C, &T);
	for (int i = 0; i < N; i++)
		scanf("%d", &arr[i]);
	
	int ini = 0, fim = inf; 
	while (ini < fim)
	{
		int meio = (ini + fim)/2;
		if (simulation(meio))
			fim = meio;
		else
			ini = meio + 1;
	}
	printf("%d\n", fim);

	return 0;
}
