#include <bits/stdc++.h>
#define inf 1000000000


using namespace std;

vector<pair<int, int> > graph[500];
int N, dist[500];

void Dijkstra(int source)
{
    for (int i = 0; i < N; i++) dist[i] = inf;
    dist[source] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > fila;
    stack<pair<int, int> > pil;
    fila.push(make_pair(dist[source], source));
    
    while (!fila.empty())
    {
        for (vector<pair<int, int> >::iterator it = graph[fila.top().second].begin(); it != graph[fila.top().second].end(); it++)
            if (dist[it->second] > fila.top().first + it->first)
            {
                dist[it->second] = fila.top().first + it->first;
                pil.push(make_pair(dist[it->second], it->second));
            }
            
        fila.pop();
        while (!pil.empty())
        {
            fila.push(make_pair(pil.top().first, pil.top().second));
            pil.pop();
        }
    }
}

int main()
{
    int E, i, X, Y, H, K, O, D;
    
    while (true)
    {
        scanf("%d %d", &N, &E);
        if (N == 0 && E == 0) return 0;
        for (i = 0; i < E; i++)
        {
            scanf("%d %d %d", &X, &Y, &H);
            for (int j = 0; j < (int)graph[Y - 1].size(); j++)
                if (graph[Y - 1][j].second == X - 1)
                {
                    graph[Y - 1][j].first = 0;
                    H = 0;
                }
            graph[X - 1].push_back(make_pair(H, Y - 1));
        }
        scanf("%d", &K);
        for (i = 0; i < K; i++)
        {
            scanf("%d %d", &O, &D);
            Dijkstra(O - 1);
            if (dist[D - 1] == inf)
                printf("Nao e possivel entregar a carta\n");
            else
                printf("%d\n", dist[D - 1]);
        }
        printf("\n");
        
        for (i = 0; i < N; i++)
            graph[i].clear();
    }
}
