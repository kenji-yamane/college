#include <cstdio>
#include <stack>
#include <queue>


using namespace std;

int main()
{
	int N, id, num;
	
	while (scanf("%d", &N) != -1)
	{
		bool isQueue = true, isStack = true, isPriorityQueue = true;
		priority_queue<int> pq;
		stack<int> s;
		queue<int> q;
		
		while (N--)
		{
			scanf("%d %d", &id, &num);
			if (id == 1)
			{
				pq.push(num);
				s.push(num);
				q.push(num);
			}
			else
			{
				if (isPriorityQueue)
				{
					if (pq.empty()) isPriorityQueue = false;
					else if (pq.top() != num) isPriorityQueue = false;
					else pq.pop();
				}
				if (isStack)
				{
					if (s.empty()) isStack = false;
					else if (s.top() != num) isStack = false;
					else s.pop();
				}
				if (isQueue)
				{
					if (q.empty()) isQueue = false;
					else if (q.front() != num) isQueue = false;
					else q.pop();
				}
			}
		}
		if (!isQueue && !isStack && !isPriorityQueue)
			printf("impossible\n");
		else if (isQueue && !isStack && !isPriorityQueue)
			printf("queue\n");
		else if (!isQueue && isStack && !isPriorityQueue)
			printf("stack\n");
		else if (!isQueue && !isStack && isPriorityQueue)
			printf("priority queue\n");
		else
			printf("not sure\n");
	}
	
	return 0;
}
