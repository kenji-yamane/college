#include <cstdio>
#include <queue>


using namespace std;

int main()
{
	int N, i;
	
	while (true)
	{
		queue<int> q;
		scanf("%d", &N);
		if (N == 0) break;
		
		for (i = 1; i <= N; i++)
			q.push(i);
		printf("Discarded cards:");
		while (q.size() != 1)
		{
			printf(" %d%c", q.front(), q.size() == 2 ? '\n' : ',');
			q.pop();
			q.push(q.front());
			q.pop();
		}
		printf("Remaining card: %d\n", q.front());
	}
	
	return 0;
}
