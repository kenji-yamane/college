#include <bits/stdc++.h>


using namespace std;

//no fundo é uma busca binária

int search(long long i, long long n, long long len)
{
	long long meio = len/2;

	if (i == meio)
		return n%2;
	else if (i > meio)
		return search(i - meio - 1, n/2, len/2 - 1);
	else
		return search(i, n/2, len/2 - 1);
}

int main()
{
	long long n, l, r, len;
	int ans = 0;

	scanf("%lld %lld %lld", &n, &l, &r);
	len = 2;
	while (len - 1 < n)
		len *= 2;
	len--; //tamanho da sequência final
	for (long long i = l; i <= r; i++)
		ans += search(i - 1, n, len - 1);
	printf("%d\n", ans);

	return 0;
}
