/***********************************/
/* Aluno: Kenji Yamane             */
/* CES-10: Introdução à Computação */
/* Prof. Victor Curtis             */
/***********************************/
#include <stdio.h>


int main ()
{
    int v[50], j, aux, size, i = 0;
    char a = ',';

    //Leitura do vetor
    while (scanf(" %d%c", &v[i], &a) != EOF)
        i++;
    
        
    
    size = i;
    
    //Ordenamento utilizando o algoritmo bubblesort
    for (i = size; i > 1; i--)
        for (j = 0; j < i - 1; j++)
            if (v[j + 1] < v[j])
            {
                aux = v[j + 1];
                v[j + 1] = v[j];
                v[j] = aux;
            }
                
    //Impressão do vetor
    for (i = 0; i < size; i++)
        printf("%d ", v[i]);
    
    printf("\n");
    
    return 0;
}
