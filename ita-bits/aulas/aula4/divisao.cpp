#include <bits/stdc++.h>


using namespace std;

int main()
{
	int N, answers, cases = 0;
	bool trespassed;
	
	while(true)
	{
		scanf("%d", &N);
		if (N != 0 && cases++ != 0) printf("\n");
		if (!N) break;
		
		answers = 0;
		trespassed = false;
		for (int f = 0; f < 10 && !trespassed; f++)
			for (int g = 0; g < 10 && !trespassed; g++)
				for (int h = 0; h < 10 && !trespassed; h++)
					for (int i = 0; i < 10 && !trespassed; i++)
						for (int j = 0; j < 10 && !trespassed; j++)
						{
							set<int> s = {f, g, h, i, j};
							if (s.size() == 5)
							{
								int denominator = 10000*f + 1000*g + 100*h + 10*i + j;
								int numerator = N*denominator;
								if (numerator > 99999)
								{
									trespassed = false;
									break;
								}
								
								int a = numerator/10000;
								int b = numerator/1000 - 10*a;
								int c = numerator/100 - 100*a - 10*b;
								int d = numerator/10 - 1000*a - 100*b - 10*c;
								int e = numerator - 10000*a - 1000*b - 100*c - 10*d;
								s.insert({a, b, c, d, e});
								if (s.size() == 10)
								{
									printf("%d / %05d = %d\n", numerator, denominator, N);
									answers++;
								}
							}
						}
		if (answers == 0) printf("There are no solutions for %d.\n", N);
	}
	
	return 0;
}
