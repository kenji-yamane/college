#include <bits/stdc++.h>


using namespace std;

//a*b + b*c + a*c = N
//b*(a + c) + a*c = N
//b*(a + c) + a*c + a*a = N + a*a
//b*(a + c) + a*(a + c) = N + a*a
//(a + b)*(a + c) = N + a*a

int main()
{
	int N, ans;
	
	while (true)
	{
		scanf("%d", &N);
		if (N == -1) break;
		
		ans = 0;
		int squareN = sqrt(N) + 1;
		for (int a = 0; a <= squareN; a++)
		{
			int square = sqrt(N + a*a) + 1;
			for (int x = 1; x <= square; x++)
				if ((N + a*a)%x == 0 && x >= 2*a && (N + a*a)/x >= 2*a)
					if ((N + a*a)/x >= x)
						ans++;
		}
		printf("%d\n", ans);
	}
	
	return 0;
}
