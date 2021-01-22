#include <bits/stdc++.h>


using namespace std;

//Melhor do que mapa, usar o proprio array que as manipulações sao O(1)

int main()
{
    int N, aux1, ans;
    char aux2;
    int key[61][2];
    
    while (scanf("%d", &N) != EOF)
    {
        memset(key, 0, sizeof(key));
        while (N--)
            scanf("%d %c", &aux1, &aux2), key[aux1][aux2 == 'D' ? 0 : 1]++;
        
        ans = 0;
        for (int i = 30; i <= 60; i++)
            while (key[i][0] > 0 && key[i][1] > 0)
                ans++, key[i][0]--, key[i][1]--;
        printf("%d\n", ans);
    }
    
    return 0;
}
