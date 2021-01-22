#include <bits/stdc++.h>


using namespace std;

//Binary Search the Answer
//Quem quiser entender melhor pode me procurar, é um algoritmo especial rs

int N, K, arr[10000];

bool simulate(int guess)
{
	int slices = 0;
	for (int i = 0; i < K; i++)
		slices += (arr[i] - arr[i]%guess)/guess;
	return (slices >= N ? true : false);
}

int main()
{
	int ini = 0, fim = 100000000;
	
	scanf("%d %d", &N, &K);
	for (int i = 0; i < K; i++) scanf("%d", &arr[i]);
	
	while (ini < fim) //O(log(100000000))
	{
		int meio = (ini + fim)/2 + 1;
		if (simulate(meio) == true) //O(K)
			ini = meio;
		else
			fim = meio - 1;
	}
	printf("%d\n", fim);
	
	return 0;
}
