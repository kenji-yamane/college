/***********************************/
/* Aluno: Kenji Yamane             */
/* CES-10: Introdução à Computação */
/* Prof. Victor Curtis             */
/***********************************/
#include <stdio.h>
#include <stdbool.h>



//Function that determines maximum use of ceil average
int max_ceil_average (int N, int M, int Sum)
{
    int c, i = 0;
    
    while ((M + 1)*i + M*(N - i) <= Sum)
    {
        c = i;
        i++;
    }
    
    return c;
}

//Rectifies c considering numbers that are already at ceil average and returns c
int rectifier_c (int v, int M, int c, int flux)
{
    if (v == M + 1)
        c--;
    if (c < 0)
    {
        v = M;
        c++;
        flux++;
    }
    
    return c;
}

//Rectifies c considering numbers that are already at ceil average and returns flux
int rectifier_flux (int v, int M, int c, int flux)
{
    if (v == M + 1)
        c--;
    if (c < 0)
    {
        v = M;
        c++;
        flux++;
    }
    
    return flux;
}


int main ()
{   
    int N;
    
    while (true)
    {
        double R;
        int v[1000], M, c, integer, decimal, i = 0, flux = 0, Sum = 0;
        char p;
        
        scanf("%d", &N);
        
        if (N == 0)
            return 0;
        
        for (i = 0; i < N; i++)
        {
            scanf("%d %c %d", &integer, &p, &decimal);
            v[i] = 100*integer + decimal;
            Sum += v[i];
        }
        if (Sum%N == 0)
        {
            M = Sum/N;
            for (i = 0; i < N; i++)
                if (v[i] >= M)
                    flux += v[i] - M;
            
            R = 0.01*flux;
            
            printf("$%.2lf\n", R);
        }
        else
        {
            M = Sum/N;
            
            c = max_ceil_average (N, M, Sum);                
            
            for (i = 0; i < N; i++)
            {
                c = rectifier_c (v[i], M, c, flux);
                flux = rectifier_flux (v[i], M, c, flux);
            }
            for (i = 0; i < N; i++)
            {
                if (v[i] > (M + 1) && c > 0)
                {
                    flux += v[i] - (M + 1);
                    v[i] = (M + 1);
                    c--;
                }
            }
            for (i = 0; i < N; i++)
                if (v[i] > (M + 1) && c <= 0)
                    flux += v[i] - M;
            
            R = 0.01*flux;
            
            printf("$%.2lf\n", R);
        } 
    }
}



