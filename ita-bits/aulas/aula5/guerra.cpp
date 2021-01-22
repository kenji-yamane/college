#include <bits/stdc++.h>


using namespace std;

int main()
{
	int S, i, nlog[100000], quad[100000], ini, wins = 0;
	
	scanf("%d", &S);
	for (i = 0; i < S; i++)
		scanf("%d", &quad[i]);
	for (i = 0; i < S; i++)
		scanf("%d", &nlog[i]);
	ini = 0;
	
	sort(nlog, nlog + S, greater<int>());
	sort(quad, quad + S, greater<int>());
	
	for (i = 0; i < S; i++)
		if (quad[i] < nlog[ini])
			wins++, ini++;
	printf("%d\n", wins);
	
	return 0;
}
