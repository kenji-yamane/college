#include <bits/stdc++.h>


using namespace std;

int main()
{
	int scenarios, N, d, xRat, yRat, i, maximum;
	bool found;
	
	scanf("%d", &scenarios);
	while (scenarios--)
	{
		int manhattan[1025][1025] = {{}};
		scanf("%d", &d);
		scanf("%d", &N);
		while (N--)
		{
			scanf("%d %d %d", &xRat, &yRat, &i);
			for (int x = max(xRat - d, 0); x <= min(xRat + d, 1024); x++)
				for (int y = max(yRat - d, 0); y <= min(yRat + d, 1024); y++)
					manhattan[y][x] += i;
		}
		
		found = false;
		maximum = 0;
		for (int i = 0; i < 1025; i++)
			for (int j = 0; j < 1025; j++)
				maximum = max(maximum, manhattan[i][j]);
		for (int x = 0; x < 1025 && !found; x++)
			for (int y = 0; y < 1025 && !found; y++)
				if (manhattan[y][x] == maximum)
				{
					printf("%d %d %d\n", x, y, manhattan[y][x]);
					found = true;
				}
	}
	
	return 0;
}
