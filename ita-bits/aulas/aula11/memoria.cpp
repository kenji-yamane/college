#include <bits/stdc++.h>

#define MAXN 50000


using namespace std;

vector<int> graph[MAXN];
int depth[MAXN], parent[MAXN];
bool visited[MAXN];

void BFS(int source)
{
    depth[source] = 0;
    visited[source] = true;
    queue<int> fila;
    fila.push(source);
    
    while (!fila.empty())
    {
        for (vector<int>::iterator it = graph[fila.front()].begin(); it != graph[fila.front()].end(); it++)
            if (visited[*it] == false)
            {
                fila.push(*it);
                visited[*it] = true;
                depth[*it] = depth[fila.front()] + 1;
                parent[*it] = fila.front();
            }
        
        fila.pop();
    }
}

int findDistance(int a, int b)
{
    int ans = 0;
    
    while (depth[a] > depth[b])
    {
        ans++;
        a = parent[a];
    }
    while (depth[b] > depth[a])
    {
        ans++;
        b = parent[b];
    }
    while (a != b)
    {
        ans += 2;
        a = parent[a];
        b = parent[b];
    }
    
    return ans;
}

int main()
{
    int N, i, C, A, B, ans = 0;
    vector<int> equality[MAXN/2];
    
    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf("%d", &C);
        equality[C - 1].push_back(i);
    }
    
    for (i = 0; i < N - 1; i++)
    {
        scanf("%d %d", &A, &B);
        graph[A - 1].push_back(B - 1);
        graph[B - 1].push_back(A - 1);
    }
    
    BFS(0);
    
    for (i = 0; i < N/2; i++)
        ans += findDistance(equality[i].front(), equality[i].back());
    
    printf("%d\n", ans);
    
    return 0;
}
