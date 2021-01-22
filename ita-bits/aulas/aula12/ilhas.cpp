#include <bits/stdc++.h>
#define MAXN 1000
#define MAXM 100000
#define inf 99999999


using namespace std;

vector<pair<int, int> >graph[MAXN];
int N, dist[MAXN];

void Dijkstra(int source)
{
    for (int i = 0; i < N; i++) dist[i] = inf;
    dist[source] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    stack<pair<int, int> > pil;
    pq.push(make_pair(dist[source], source));
    
    while (!pq.empty())
    {
        for (vector<pair<int, int> >::iterator it = graph[pq.top().second].begin(); it != graph[pq.top().second].end(); it++)
            if (dist[it->second] > pq.top().first + it->first)
            {
                dist[it->second] = pq.top().first + it->first;
                pil.push(make_pair(dist[it->second], it->second));
            }
        
        pq.pop();
        while (!pil.empty())
        {
            pq.push(make_pair(pil.top().first, pil.top().second));
            pil.pop();
        }
    }
}

int main()
{
    int M, i, U, V, P, S, least, most;
    
    scanf("%d %d", &N, &M);
    for (i = 0; i < M; i++)
    {
        scanf("%d %d %d", &U, &V, &P);
        graph[U - 1].push_back(make_pair(P, V - 1));
        graph[V - 1].push_back(make_pair(P, U - 1));
    }
    scanf("%d", &S);
    Dijkstra(S - 1);
    least = inf;
    most = 0;
    for (i = 0; i < N; i++)
    {
        if (i != S - 1)
            least = min(least, dist[i]);
        most = max(most, dist[i]);
    }
    printf("%d\n", most - least);
    
    return 0;
}
