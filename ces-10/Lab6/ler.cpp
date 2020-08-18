#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>


int main ()
{
    FILE *lab = NULL;
    char charac, before = ' ', *arq = "Lab6-1.md";
    int notspace = 0, words = 0, lines = 0;
    
    lab = fopen (arq, "r");
        
    if (lab == NULL)
        return 0;
    
    while (fscanf (lab, "%c", &charac) != EOF)
    {
        if (isspace (charac) == false)
            notspace++;
        else if (isspace (before) == false)
            words++;
        if (charac == '\n')
            lines++;
            
        before = charac;
    }
    
    printf ("Quantidade de linhas: %d\n", lines + 1);
    printf ("Quantidade de palavras: %d\n", words);
    printf ("Quantidade de caracteres não whitespace: %d\n", notspace);   
    
    fclose (lab);
    
    return 0;
}

