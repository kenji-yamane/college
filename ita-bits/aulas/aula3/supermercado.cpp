#include <cstdio>
#include <queue>


using namespace std;

priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;

int main()
{
	int N, M, i, v[10000], c[10000], ctrl = 0, time;
	
	scanf("%d %d", &N, &M);
	for (i = 0; i < N; i++)
		scanf("%d", &v[i]);
	for (i = 0; i < M; i++)
		scanf("%d", &c[i]);
	
	for (i = 0; i < N; i++)
		pq.push(make_pair(v[i]*c[ctrl++], i));
	while (ctrl < M)
	{
		time = pq.top().first;
		i = pq.top().second;
		pq.pop();
		pq.push(make_pair(time + v[i]*c[ctrl++], i));
	}
	while (!pq.empty())
		time = pq.top().first, pq.pop();
	printf("%d\n", time);

	return 0;
}
