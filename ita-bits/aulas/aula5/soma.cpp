#include <bits/stdc++.h>


using namespace std;

int main()
{
	int N, aux, sum;
	bool first;
	
	while (true)
	{
		first = true;
		sum = 0;
		scanf("%d", &N);
		if (!N) return 0;
		
		for (int i = 0; i < N; i++)
		{
			scanf("%d", &aux);
			sum += aux;
			if (aux > 0 && first)
				printf("%d", aux), first = false;
			else if (aux > 0)
				printf(" %d", aux);
		}
		if (!sum) printf("0");
		printf("\n");
	}
	
	return 0;
}
