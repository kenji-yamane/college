#include <cstdio>
#include <deque>
#define inactive active == 1 ? 0 : 1


using namespace std;

int main()
{
	int N, k, m, i;
	
	while (true)
	{
		deque<int> dq[2]; //vetor de deques
		int active = 0;
		scanf("%d %d %d", &N, &k, &m);
		if (!N && !k && !m) break;
		
		for (i = 1; i <= N; i++)
			dq[active].push_back(i);

		while (dq[active].size() + dq[inactive].size() > 0)
		{
			for (i = 0; i < k - 1; i++)
			{
			    dq[inactive].push_back(dq[active].front());
			    dq[active].pop_front();
			    if (dq[active].empty())
			        active = inactive;
		    }
		    for (i = 0; i < m - 1; i++)
			{
			    dq[inactive].push_front(dq[active].back());
			    dq[active].pop_back();
			    if (dq[active].empty())
			        active = inactive;
		    }
		    
		    if (dq[active].size() == 1)
		    {
				printf("%3d%s", dq[active].front(), dq[inactive].empty() ? "\n" : ",");
				dq[active].pop_front();
				active = inactive;
			}
			else
			{
				printf("%3d%3d%s", dq[active].front(), dq[active].back(), dq[active].size() + dq[inactive].size() == 2 ? "\n" : ",");
				dq[active].pop_front();
				dq[active].pop_back();
				if (dq[active].empty())
				    active = inactive;
			}
		}
	}
	
	return 0;
}
