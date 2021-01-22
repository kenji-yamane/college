#include <bits/stdc++.h>


using namespace std;

//overkill usar priority_queue? possivelmente
//loucuras no estresse do momento rs

int main()
{
    int N, aux;
    
    while (true)
    {
        scanf("%d", &N);
        if (!N) break;
        
        while (N--)
        {
            priority_queue<pair<int, char>, vector<pair<int, char> >, greater<pair<int, char> > > pq;
            for (int i = 0; i < 5; i++)
                scanf("%d", &aux), pq.push(make_pair(aux, 'A' + i));
            
            int least = pq.top().first;
            char letterleast = pq.top().second;
            pq.pop();
            if (least > 127 || pq.top().first <= 127)
                printf("*\n");
            else
                printf("%c\n", letterleast);
        }
    }
    
    return 0;
}
