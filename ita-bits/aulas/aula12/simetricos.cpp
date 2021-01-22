#include <bits/stdc++.h>
#define MAXN 100
#define inf 99999


using namespace std;

vector<pair<int, int> > graph[MAXN*MAXN];
int N, mindis, dist[MAXN*MAXN], grid[MAXN][MAXN];
long long int ans;
bool searching;

void Dijkstra(int source)
{
    for (int i = 0; i < N*N; i++) dist[i] = inf;
    dist[source] = grid[0][0];
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > fila;
    stack<pair<int, int> > pil;
    fila.push(make_pair(dist[source], source));
    
    while (!fila.empty())
    {
        for (vector<pair<int, int> >::iterator it = graph[fila.top().second].begin(); it != graph[fila.top().second].end(); it++)
            if (dist[it->second] >= fila.top().first + it->first)
            {
                dist[it->second] = fila.top().first + it->first;
                pil.push(make_pair(dist[it->second], it->second));
                
                if (searching == true && dist[it->second] == mindis && ((it->second%N + (it->second - it->second%N)/N) == N - 1))
                {
                    ans++;
                    ans %= 1000000009;
                }
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
    int i, j, k;
    
    while (true)
    {
        scanf("%d", &N);
        if (N == 0) return 0;
        for (i = 0; i < N; i++)
            for (j = 0; j < N; j++)
                scanf("%d", &grid[i][j]);
        
        for (i = 0, k = N - 1; i < N; i++, k--)
            for (j = 0; j < k; j++)
                grid[i][j] += grid[N - 1 - j][N - 1 - i];
        for (i = 0, k = N - 1; i < N; i++, k--)
            for (j = 0; j < k; j++)
            {
                if (i < N - 1)
                    graph[i*N + j].push_back(make_pair(grid[i + 1][j], (i + 1)*N + j));
                if (i > 0)
                    graph[i*N + j].push_back(make_pair(grid[i - 1][j], (i - 1)*N + j));
                if (j < N - 1)
                    graph[i*N + j].push_back(make_pair(grid[i][j + 1], i*N + j + 1));
                if (j > 0)
                    graph[i*N + j].push_back(make_pair(grid[i][j - 1], i*N + j - 1));
            }
        
        searching = false;
        Dijkstra(0);
        mindis = inf;
        for (i = 0, j = N - 1; i < N; i++, j--)
            if (dist[i*N + j] < mindis)
                mindis = dist[i*N + j];
        
        ans = 0;
        searching = true;
        Dijkstra(0);
        printf("%lld\n", ans);
        
        for (i = 0; i < N*N; i++) graph[i].clear();
    }
}
