#include <bits/stdc++.h>


using namespace std;

int gcd(int a, int b)
{
	if (b == 0) return a;
	return gcd(b, a%b);
}

int main()
{
	int N, F1, F2;

	scanf("%d", &N);
	while (N--)
	{
		scanf("%d %d", &F1, &F2);
		printf("%d\n", gcd(F1, F2));
	}
}
