#include <bits/stdc++.h>


using namespace std;

int main()
{
    int N, i, arr[100000], sum, j, k, partition, ans;
    int counted[100001];
    
    while (scanf("%d", &N) != EOF)
    {
        ans = sum = 0;
        for (i = 0; i < N; i++)
        {
            scanf("%d", &arr[i]);
            sum += arr[i];
        }
        
        if (sum%3 != 0)
            printf("0\n");
        else
        {
            memset(counted, 0, sizeof(counted));
            sum /= 3;
            partition = j = k = 0;
            while (k < N && j < N)
            {
                while (partition != sum && k < N && j < N)
                    if (partition < sum)
                        partition += arr[k++];
                    else
                        partition -= arr[j++];
                if (partition == sum)
                {
                    if (k < N) counted[j]++;
                    if (k < N) counted[k]++;
                    partition -= arr[j++];
                }
            }
            for (i = 0; i < N; i++) if (counted[i] == 2) ans++;
            printf("%d\n", ans);
        }
    }
    
    return 0;
}
