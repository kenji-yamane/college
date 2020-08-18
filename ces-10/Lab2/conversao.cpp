/***********************************/
/* Aluno: Kenji Yamane             */
/* CES-10: Introdução à Computação */
/* Prof. Victor Curtis             */
/***********************************/
#include <stdio.h>


void binary_conversion (int N)
{
    int aux, i;
    char v[9];
    v[8] = '\0';
    
    for (i = 7; i != -1; i--)
    {
        aux = N%2;
        N = (N - aux)/2;
        if (aux == 0)
            v[i] = '0';
        else
            v[i] = '1';
    }   
    
    printf("%s\n", v);
}

int main ()
{
    int N;
    
    scanf("%d", &N);
    
    if (N > 255) 
        printf("ERRO\n");
    else
        binary_conversion(N);
    
    return 0;
}
