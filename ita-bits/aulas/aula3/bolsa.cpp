#include <cstdio>
#include <queue>


using namespace std;

int main()
{
	int N, value, ans, valuex, valuey;
	char id;
	
	while (true)
	{
		priority_queue<int> buys;
		priority_queue<int, vector<int>, greater<int> > sells;
		scanf("%d", &N);
		if (!N) break;
		
		ans = 0;
		while (N--)
		{
			scanf(" %c %d.%d", &id, &valuex, &valuey);
			value = 100*valuex + valuey;
			if (id == 'C') buys.push(value);
			else		   sells.push(value);
			
			while (!buys.empty() && !sells.empty() && buys.top() >= sells.top())
				ans += buys.top() - sells.top(), buys.pop(), sells.pop();
		}
		printf("%d.%02d\n", ans/100, ans - (ans/100)*100);
	}
	
	return 0;
}
