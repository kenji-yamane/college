#include <bits/stdc++.h>


using namespace std;

//Força bruta/Dividir para conquistar

int main()
{
    long long N, i, j, c, before, ans;
    pair<long long, long long> points[1000];
    vector<long long> distances;
    
    while (true)
    {
        ans = 0;
        scanf("%lld", &N);
        if (N == 0) return 0;
        
        for (i = 0; i < N; i++)
            scanf("%lld %lld", &points[i].first, &points[i].second);
        
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
                distances.push_back(pow(points[j].first - points[i].first, 2) + pow(points[j].second - points[i].second, 2));
            sort(distances.begin(), distances.end());
            
            c = 1;
            before = -1;
            for (vector<long long>::iterator it = distances.begin(); it != distances.end(); it++)
            {
                if (*it == before)
                    c++;
                else
                {
                    ans += c*(c - 1)/2;
                    c = 1;
                }
                before = *it;
            }
            ans += c*(c - 1)/2;
            distances.clear();
        }
        
        printf("%lld\n", ans);
    }
}
