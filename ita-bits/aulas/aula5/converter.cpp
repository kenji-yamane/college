#include <bits/stdc++.h>


using namespace std;

int main()
{
	int T, x, fib[23], i, ans;
	bool used[23];
	
	fib[0] = fib[1] = 1;
	for (int i = 2; i < 23; i++)
		fib[i] = fib[i - 1] + fib[i - 2];
	
	scanf("%d", &T);
	while (T--)
	{
		ans = 0;
		memset(used, false, sizeof(used));
		scanf("%d", &x);
		while (x != 0)
		{
			for (i = 1; x >= fib[i]; i++);
			used[i - 1] = true;
			x -= fib[i - 1];
		}
		for (int i = 1; i < 21; i++)
			if (used[i] && used[i + 1] && !used[i + 2])
				used[i] = false, used[i + 1] = false, used[i + 2] = true;
		for (int i = 0; i < 22; i++)
			used[i] = used[i + 1];
		for (int i = 1; i < 23; i++)
			if (used[i])
				ans += fib[i];
		printf("%d\n", ans);
	}
	
	return 0;
}
