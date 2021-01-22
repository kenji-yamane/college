#include <bits/stdc++.h>
#define inf 9999999


using namespace std;

vector<pair<int, int> > graph[500];
int N, D, dist[500], ancestor[500];

void Dijkstra(int a)
{
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    stack<pair<int, int> > pil;
    pq.push(make_pair(dist[a], a));
    for (int i = 0; i < N; i++) dist[i] = inf;
    dist[a] = 0;
    
    while (!pq.empty())
    {
        for (vector<pair<int, int> >::iterator it = graph[pq.top().second].begin(); it != graph[pq.top().second].end(); it++)
            if (dist[it->second] >= dist[pq.top().second] + it->first)
            {
                ancestor[it->second] = pq.top().second;
                dist[it->second] = dist[pq.top().second] + it->first;
                pil.push(make_pair(dist[it->second], it->second));
            }
        
        if (pq.top().second == D) return;
        pq.pop();
        while (!pil.empty())
        {
            pq.push(make_pair(pil.top().first, pil.top().second));
            pil.pop();
        }
    }
}

void DeleteShortest(int source, int dest)
{
    if (dest == source) return;
    
    for(vector<pair<int, int> >::iterator it = graph[ancestor[dest]].begin(); it != graph[ancestor[dest]].end(); it++)
        if (it->second == dest)
        {
            graph[ancestor[dest]].erase(it);
            break;
        }
    DeleteShortest(source, ancestor[dest]);
}

int main()
{
    int M, i, S, U, V, P, original;
    
    while (true)
    {
        scanf("%d %d", &N, &M);
        if (N == 0 && M == 0) return 0;
        scanf("%d %d", &S, &D);
        for (i = 0; i < M; i++)
        {
            scanf("%d %d %d", &U, &V, &P);
            graph[U].push_back(make_pair(P, V));
        }
        
        Dijkstra(S);
        if (dist[D] == inf)
            printf("-1\n");
        else
        {
            original = dist[D];
            while (dist[D] == original)
            {
                DeleteShortest(S, D);
                Dijkstra(S);
            }
            printf("%d\n", dist[D] == inf ? -1 : dist[D]);
        }
        for (i = 0; i < N; i++)
            graph[i].clear();
    }
}
