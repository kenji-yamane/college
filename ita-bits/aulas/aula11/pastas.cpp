#include <bits/stdc++.h>


using namespace std;

int v[1000];

int main ()
{
    int N, P, a, i, quotient, rest;
    bool perfect = true;
    
    scanf ("%d %d", &P, &N);
    
    for (i = 0; i < N; i++)
    {
        scanf ("%d", &a);
        v[a - 1]++;
    }
    quotient = N/P;
    rest = N - P*quotient;
    
    for (i = 0; i < P; i++)
        if (rest != 0)
        {
            if (v[i] != quotient + 1)
                perfect = false;
            rest--;
        }
        else 
            if (v[i] != quotient)
                perfect = false;
                
    printf ("%c\n", perfect == true ? 'S' : 'N');
    
    return 0;
}
