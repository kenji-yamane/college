#include <cstdio>
#include <queue>


using namespace std;

int main()
{
	int NC, n, k, i;
	
	scanf("%d", &NC);
	for (i = 0; i < NC; i++)
	{
		queue<int> q;
		scanf("%d %d", &n, &k);
		for (int j = 1; j <= n; j++)
			q.push(j);
		
		while (q.size() != 1)
		{
			for (int j = 0; j < k - 1; j++)
				q.push(q.front()), q.pop();
			q.pop();
		}
		printf("Case %d: %d\n", i + 1, q.front());
	}
	
	return 0;
}
