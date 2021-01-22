#include <bits/stdc++.h>


using namespace std;

long long memo[200001][3];
char road[200001];
int n, a, b;

long long vertical(int posic, int height)
{
	if (posic == n) return (height == 1 ? 0 : a);
	if (memo[posic][height] != -1) return memo[posic][height];

	if (posic == 0) //primeiro tem que obrigatoriamente permanecer na altura 1
		return memo[posic][height] = vertical(posic + 1, 1);
	else if (road[posic] == '1') //tem que aumentar para 2
		return memo[posic][height] = (height == 1 ? a : 0) + b + vertical(posic + 1, 2);
	else if (road[posic - 1] == '1') //tem que manter em 2
		return memo[posic][height] = b + vertical(posic + 1, 2);
	else if (height == 1) //pode ser 1 ou 2
		return memo[posic][height] = min(vertical(posic + 1, 1), a + b + vertical(posic + 1, 2));
	else //pode ser 1 ou 2
		return memo[posic][height] = min(b + vertical(posic + 1, 2), a + vertical(posic + 1, 1));
}

int main()
{
	int T;
	long long essential;

	scanf("%d", &T);
	while (T--)
	{
		scanf("%d %d %d", &n, &a, &b);
		scanf(" %s", road);

		for (int i = 0; i < n; i++)
			memo[i][1] = memo[i][2] = -1;
		essential = (long long)n*(a + b) + b;
		printf("%lld\n", essential + vertical(0, 1));
	}

	return 0;
}
