#include <bits/stdc++.h>
#define inf 99999999


using namespace std;

vector<pair<double, int> > graph[500];
pair<double, double> people[500];
int n;
double dist[500];
bool visited[500];

double Prim(int source)
{
    priority_queue<pair<double, int>, vector<pair<double, int> >, greater<pair<double, int> > > fila;
    for (int i = 0; i < n; i++) dist[i] = inf;
    dist[source] = 0;
    fila.push(make_pair(dist[source], source));
    stack<pair<double, int> > pil;
    
    while (!fila.empty())
    {
        for (vector<pair<double, int> >::iterator it = graph[fila.top().second].begin(); it != graph[fila.top().second].end(); it++)
            if (visited[it->second] == false)
                pil.push(make_pair(it->first, it->second));
        
        if (visited[fila.top().second] == false)
            dist[fila.top().second] = fila.top().first;
        visited[fila.top().second] = true;
        
        while (!fila.empty() && visited[fila.top().second] == true)
            fila.pop();
        while (!pil.empty())
        {
            fila.push(make_pair(pil.top().first, pil.top().second));
            pil.pop();
        }
    }
    
    double ans = 0;
    for (int i = 0; i < n; i++)
        ans += dist[i];
    return ans;
}

int main()
{
    int C, i, j, k;
    
    scanf("%d", &C);
    
    for (k = 0; k < C; k++)
    {
        scanf("%d", &n);
        for (i = 0; i < n; i++)
            scanf("%lf %lf", &people[i].first, &people[i].second);
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                if (i != j)
                    graph[i].push_back(make_pair(sqrt(pow(people[i].first - people[j].first, 2) + 
                                                      pow(people[i].second - people[j].second, 2)), j));
        
        printf("%.2lf\n", Prim(0)/100);
        for (i = 0; i < n; i++) graph[i].clear();
        memset(visited, false, sizeof(visited));
    }
    return 0;
}
