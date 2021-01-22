#include <bits/stdc++.h>


using namespace std;

int main()
{
    int C, N, T, D, time = 0, ans = 0;
    queue<pair<int, int> > fila;
    priority_queue<int, vector<int>, greater<int> > caixas;
    
    scanf("%d %d", &C, &N);
    
    while (N--)
    {
        scanf("%d %d", &T, &D);
        fila.push(make_pair(T, D));
    }
    
    while (!fila.empty())
    {   
        while ((int)caixas.size() >= C)
            time = max(time, caixas.top()), caixas.pop();
        
        if (time - fila.front().first > 20)
            ans++;
        
        time = max(time, fila.front().first);
        caixas.push(time + fila.front().second);
        fila.pop();
    }
    
    printf("%d\n", ans);
    
    return 0;
}
