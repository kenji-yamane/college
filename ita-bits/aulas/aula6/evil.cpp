#include <bits/stdc++.h>


using namespace std;

//evolve bastante bit-wise operations
//n tem problema não saber, é assunto da penúltima aula
//a ideia é ir dividindo o vetor conforme o bit for 0 ou 1

int arr[100000], ans, diminished;

void constructAns(int ini, int fim, int bits)
{
	if (bits == -1)
	{
		ans = max(ans, diminished);
		return;
	}
	int ones = 0;
	int firstOne = -1;
	for (int i = ini; i < fim; i++)
	{
		ones += ((1 << bits)&arr[i]) == 0 ? 0 : 1;
		if (firstOne == -1 && (((1 << bits)&arr[i]) != 0))
			firstOne = i;
	}
	if (ones == 0 || ones == (fim - ini))
	{
		diminished += (1 << bits);
		constructAns(ini, fim, bits - 1);
		diminished -= (1 << bits);
	}
	else
	{
		constructAns(ini, firstOne, bits - 1);
		constructAns(firstOne, fim, bits - 1);
	}
}

int main()
{
	int n, bits = 0, minMax = 0;

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &arr[i]);
	sort(arr, arr + n);
	while ((arr[n - 1] >> (bits + 1)) != 0)
		bits++;

	constructAns(0, n, bits);
	for (int i = bits; i >= 0; i--)
		if (((1 << i)&ans) == 0)
			minMax += (1 << i);
	printf("%d\n", minMax);

	return 0;
}
