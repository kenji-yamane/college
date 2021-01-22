#include <bits/stdc++.h>
#define MAXV 64


using namespace std;

vector<int> graph[MAXV];
int dist[MAXV];
bool visited[MAXV];

void BreadthFirstSearch(int source)
{
    queue<int> fila;
    fila.push(source);
    visited[source] = true;
    
    while (!fila.empty())
    {
        for (vector<int>::iterator it = graph[fila.front()].begin(); it != graph[fila.front()].end(); it++)
            if (visited[*it] == false)
            {
                visited[*it] = true;
                dist[*it] = dist[fila.front()] + 1;
                fila.push(*it);
            }
        
        fila.pop();
    }
}

int main()
{
    int i, j;
    char a, b, c, d;
    
    for (i = 0; i < 8; i++)
        for (j = 0; j < 8; j++)
        {
            if (i + 1 < 8 && j - 2 >= 0)
                graph[8*i + j].push_back(8*(i + 1) + j - 2);
            if (i + 1 < 8 && j + 2 < 8)
                graph[8*i + j].push_back(8*(i + 1) + j + 2);
            if (i + 2 < 8 && j - 1 >= 0)
                graph[8*i + j].push_back(8*(i + 2) + j - 1);
            if (i + 2 < 8 && j + 1 < 8)
                graph[8*i + j].push_back(8*(i + 2) + j + 1);
            if (i - 2 >= 0 && j + 1 < 8)
                graph[8*i + j].push_back(8*(i - 2) + j + 1);
            if (i - 2 >= 0 && j - 1 >= 0)
                graph[8*i + j].push_back(8*(i - 2) + j - 1);
            if (i - 1 >= 0 && j + 2 < 8)
                graph[8*i + j].push_back(8*(i - 1) + j + 2);
            if (i - 1 >= 0 && j - 2 >= 0)
                graph[8*i + j].push_back(8*(i - 1) + j - 2);
        }
        
    while (scanf(" %c%c %c%c", &a, &b, &c, &d) != EOF)
    {
        BreadthFirstSearch(a - 'a' + 8*(b - '1'));
        
        printf("To get from %c%c to %c%c takes %d knight moves.\n", a, b, c, d, dist[c - 'a' + 8*(d - '1')]);
        memset(dist, 0, 64*sizeof(int));
        memset(visited, false, 64*sizeof(bool));
    }
    
    return 0;
}
