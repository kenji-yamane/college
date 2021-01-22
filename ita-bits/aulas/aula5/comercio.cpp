#include <bits/stdc++.h>


using namespace std;

int main()
{
	int N, aux, minimum;
	queue<pair<int, int> > sells, buys;
	long long ans;
	
	while (true)
	{
		ans = 0;
		scanf("%d", &N);
		if (!N) break;
		for (int i = 0; i < N; i++)
		{
			scanf("%d", &aux);
			if (aux > 0)
				buys.push(make_pair(aux, i));
			else if (aux < 0)
				sells.push(make_pair(-aux, i));
		}
		while (!buys.empty())
		{
			minimum = min(buys.front().first, sells.front().first);
			buys.front().first -= minimum;
			sells.front().first -= minimum;
			ans += minimum*(abs(buys.front().second - sells.front().second));
			if (buys.front().first == 0)
				buys.pop();
			else
				sells.pop();
		}
		printf("%lld\n", ans);
	}
	
	return 0;
}
