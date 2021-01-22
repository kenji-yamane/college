#include <bits/stdc++.h>


using namespace std;

int main()
{
    long long int fat;
    int T, i, N;
    char K[21];
    
    scanf("%d", &T);
    for (i = 0; i < T; i++)
    {
        fat = 1;
        scanf("%d%[!]", &N, K);
        
        while (N > 0)
        {
            fat *= N;
            N -= (int)strlen(K);
        }
        printf("%lld\n", fat);
    }
    
    return 0;
}
