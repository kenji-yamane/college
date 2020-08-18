#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


bool Search (int x, int* list, int* ini, int* fim)
{
    int middle = (*ini + *fim)/2;
    
    if (x > list[middle])
        *ini = middle + 1;
    if (x == list[middle])
        return true;
    if (x < list[middle])
        *fim = middle - 1;
    if (*fim < *ini)
        return false;
    
    return Search (x, list, ini, fim);
}

int main ()
{
    int n, x, i;
    int *list, *ini, *fim;
    bool found;
    
    if (scanf ("%d\n%d\n", &n, &x) != 2)
        exit (-1);
        
    list = (int*)malloc (n*sizeof(int));
    ini = (int*)malloc (sizeof(int));
    fim = (int*)malloc (sizeof(int));
    *ini = 0;
    *fim = n - 1;
        
    for (i = 0; i < n; i++)
        if (scanf ("%d,", list + i) != 1)
            exit (-1);
    
    found = Search (x, list, ini, fim);
    
    if (found == true)
        printf ("%d\n", (*ini + *fim)/2);
    else 
        printf ("-1\n");
    
    free (list);
    free (ini);
    free (fim);
    
    return 0;
}
