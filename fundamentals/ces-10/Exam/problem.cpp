/***********************************/
/* Aluno: Kenji Yamane             */
/* CES-10: Introdução à Computação */
/* Prof. Victor Curtis             */
/***********************************/
#include <stdio.h>
#include <stdbool.h>


int cycle_length (int x)
{
    int meter = 1;
    
    while (x != 1)
    {
        x = x%2 == 0 ? x/2 : 3*x + 1;
        meter++;
    }
    
    return meter;
}

int main ()
{
    int i, j, k, aux;
    
    while (scanf("%d %d", &i, &j) != EOF)
    {       
        int maximum = i > j ? i : j, minimum = i > j ? j : i;
        
        if (maximum > 1000000 || minimum <= 0)
            return -1;
        
        aux = cycle_length(minimum);
        
        for (k = minimum; k < maximum; k++)
            if (aux < cycle_length(k + 1))
                aux = cycle_length(k + 1);
        
        printf("%d %d %d\n", i, j, aux);
    }   
    return 0;
}
