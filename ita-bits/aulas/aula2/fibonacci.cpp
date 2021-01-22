#include <cstdio>
#include <deque>


using namespace std;

int main()
{
	int T, k, N, i;
	deque<long long> dq;
	
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d %d", &k, &N);
		if (N <= k)
			printf("%d\n", N - 1);
		else
		{
			for (i = 0; i < k; i++)
				dq.push_front(i);
			dq.push_front(((long long)k*(long long)(k - 1)/2)%1000007);
			
			for (i = 0; i < N - k - 1; i++)
			{
				dq.push_front((2*dq.front() - dq.back() + 1000007)%1000007);
				dq.pop_back();
			}
			printf("%lld\n", dq.front());
		}
		dq.clear();
	}
	
	return 0;
}
