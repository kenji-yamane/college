#include <bits/stdc++.h>


using namespace std;

void to32(unsigned long long N)
{
	if (N == 0) return;
	
	to32((N - N%32)/32);
	printf("%c", (N%32 < 10 ? N%32 + '0' : N%32 + 'A' - 10));
}

int main()
{
	unsigned long long N;

	while (true)
	{
		scanf("%llu", &N);
		if (!N) break;

		to32(N);
		printf("\n");
	}
	printf("0\n");

	return 0;
}
