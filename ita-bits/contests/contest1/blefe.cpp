#include <bits/stdc++.h>


using namespace std;

//usar as propriedades logarítmicas de set safa o TLE
//por pouco mas safa

int main()
{
    int N, M, A[1000], B[10000];
    set<int> s;
    
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]), s.insert(A[i]);
    for (int i = 0; i < M; i++)
        scanf("%d", &B[i]);
    for (int i = 0; i < M; i++)
        if (s.find(B[i]) == s.end())
        {
            bool found = false;
            for (int j = 0; j < i && found == false; j++)
                if (s.find(B[i] - B[j]) != s.end())
                    found = true;
            s.insert(B[i]);
            if (found == false)
            {
                printf("%d\n", B[i]);
                return 0;
            }
        }
    printf("sim\n");
    
    return 0;
}
