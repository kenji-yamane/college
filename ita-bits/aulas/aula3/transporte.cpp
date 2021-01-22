#include <stdio.h>
#include <algorithm>

//algoritmo diferenciado de Binary Search The Answer

using namespace std;

int main()
{
	int N, p, c, f, w[100], sum, ini, fim;
	
	scanf("%d", &N);
	while (N--)
	{
		ini = sum = 0;
		scanf("%d %d %d", &p, &c, &f);
		for (int i = 0; i < p; i++) scanf("%d", &w[i]), sum += w[i], ini = max(ini, w[i]);
		fim = sum;
		
		while (ini < fim)
		{
			int accumulated = w[0], meio = (ini + fim)/2, trucks = 1;
			for (int i = 1; i < p; i++)
				if (accumulated + w[i] <= meio)
					accumulated += w[i];
				else
					trucks++, accumulated = w[i];
			if (trucks <= c) fim = meio;
			else             ini = meio + 1;
		}
		printf("%d $%d\n", ini, ini*c*f);
	}
	
	return 0;
}
