#include <stdio.h>


int factorial(int N)
{
    int a = 0;
    
    if (N == 1)
        return 1;
    for (int i = 0; i < N; i++)
        a += factorial(N - 1);
        
    return a;
}

int main()
{
    int N;
    
    scanf("%d", &N);
    
    printf("%d\n", factorial(N));
    
    return 0;
}
