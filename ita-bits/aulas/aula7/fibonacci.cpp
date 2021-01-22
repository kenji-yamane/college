#include <bits/stdc++.h>


using namespace std;

int calls;

int fib(int n)
{
	calls++;
	if (n == 0 || n == 1) return n;
	return fib(n - 1) + fib(n - 2);
}

int main()
{
	int N, aux, ans;

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		calls = 0;
		scanf("%d", &aux);
		ans = fib(aux);
		printf("fib(%d) = %d calls = %d\n", aux, calls - 1, ans);
	}

	return 0;
}
