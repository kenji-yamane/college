/***********************************/
/* Aluno: Kenji Yamane             */
/* CES-10: Introdução à Computação */
/* Prof. Victor Curtis             */
/***********************************/
#include <stdio.h>
#include <string.h>


int main ()
{
    char str[33], aux;
    int inv_pos, size, i;
    
    while (scanf("%s", str) != EOF)
    {
        inv_pos = strlen(str)/2 + 1;
        size = strlen(str);      
        
        for (i = 0; i < inv_pos; i++)
        {
            aux = str[size - 1 - i];
            str[size - 1 - i] = str[i];
            str[i] = aux;
        }
        
        printf("%s\n", str);
    }
    
    return 0;
}
