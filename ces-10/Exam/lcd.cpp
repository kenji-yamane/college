/***********************************/
/* Aluno: Kenji Yamane             */
/* CES-10: Introdução à Computação */
/* Prof. Victor Curtis             */
/***********************************/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


//Function that prints blank spaces

void blankspace (int x)
{
    for (int i = 0; i < x; i++)
        printf(" ");
}

//Function that prints a bar to the left

void barleft (int s)
{
    printf("|");
    blankspace(s + 1);
}

//Function that prints a bar to the right

void barright (int s)
{
    blankspace(s + 1);
    printf("|");
}

//Function that prints one bar to the right and one to the left

void barboth (int s)
{
    printf("|");
    blankspace(s);
    printf("|");
}

//Function that prints traces

void traces (int s)
{
    blankspace(1);
    for (int i = 0; i < s; i++)
        printf("-");
    blankspace(1);
}

//The next ten functions print one line of a number

void LCD0 (int s, int line)
{
    if (line == 0)
        traces(s);
    if (line > 0 && line < s + 1)
        barboth(s);
    if (line == s + 1)
        blankspace(s + 2);
    if (line > s + 1 && line < (2*s + 2))
        barboth(s);
    if (line == 2*s + 2)
        traces(s);
}

void LCD1 (int s, int line)
{
    if (line == 0)
        blankspace(s + 2);
    if (line > 0 && line < s + 1)
        barright(s);
    if (line == s + 1)
        blankspace(s + 2);
    if (line > s + 1 && line < (2*s + 2))
        barright(s);
    if (line == 2*s + 2)
        blankspace(s + 2);
}

void LCD2 (int s, int line)
{
    if (line == 0)
        traces(s);
    if (line > 0 && line < s + 1)
        barright(s);
    if (line == s + 1)
        traces(s);
    if (line > s + 1 && line < (2*s + 2))
        barleft(s);
    if (line == 2*s + 2)
        traces(s);
}

void LCD3 (int s, int line)
{
    if (line == 0)
        traces(s);
    if (line > 0 && line < s + 1)
        barright(s);
    if (line == s + 1)
        traces(s);
    if (line > s + 1 && line < (2*s + 2))
        barright(s);
    if (line == 2*s + 2)
        traces(s);
}

void LCD4 (int s, int line)
{
    if (line == 0)
        blankspace(s + 2);
    if (line > 0 && line < s + 1)
        barboth(s);
    if (line == s + 1)
        traces(s);
    if (line > s + 1 && line < (2*s + 2))
        barright(s);
    if (line == 2*s + 2)
        blankspace(s + 2);
}

void LCD5 (int s, int line)
{
    if (line == 0)
        traces(s);
    if (line > 0 && line < s + 1)
        barleft(s);
    if (line == s + 1)
        traces(s);
    if (line > s + 1 && line < (2*s + 2))
        barright(s);
    if (line == 2*s + 2)
        traces(s);
}

void LCD6 (int s, int line)
{
    if (line == 0)
        traces(s);
    if (line > 0 && line < s + 1)
        barleft(s);
    if (line == s + 1)
        traces(s);
    if (line > s + 1 && line < (2*s + 2))
        barboth(s);
    if (line == 2*s + 2)
        traces(s);
}

void LCD7 (int s, int line)
{
    if (line == 0)
        traces(s);
    if (line > 0 && line < s + 1)
        barright(s);
    if (line == s + 1)
        blankspace(s + 2);
    if (line > s + 1 && line < (2*s + 2))
        barright(s);
    if (line == 2*s + 2)
        blankspace(s + 2);
}

void LCD8 (int s, int line)
{
    if (line == 0)
        traces(s);
    if (line > 0 && line < s + 1)
        barboth(s);
    if (line == s + 1)
        traces(s);
    if (line > s + 1 && line < (2*s + 2))
        barboth(s);
    if (line == 2*s + 2)
        traces(s);
}

void LCD9 (int s, int line)
{
    if (line == 0)
        traces(s);
    if (line > 0 && line < s + 1)
        barboth(s);
    if (line == s + 1)
        traces(s);
    if (line > s + 1 && line < (2*s + 2))
        barright(s);
    if (line == 2*s + 2)
        traces(s);
}

//Function that prints the line of a given number 

void printline (char a, int s, int line)
{
    switch (a)
    {
        case '0':
            LCD0(s, line);
            break;               
        case '1':
            LCD1(s, line);
            break;
        case '2':
            LCD2(s, line);
            break;
        case '3':
            LCD3(s, line);
            break;
        case '4':
            LCD4(s, line);
            break;
        case '5':
            LCD5(s, line);
            break;
        case '6':
            LCD6(s, line);
            break;
        case '7':
            LCD7(s, line);
            break;
        case '8':
            LCD8(s, line);
            break;
        case '9':
            LCD9(s, line);
            break;
        default:
            break;
    }
}

int main ()
{
    int s;
    char a[10];
    
    //while (true)
    //{   
        scanf("%d", &s);
        scanf(" %s", a);
        
        if (s == 0 && strcmp(a, "0") == 0)
            return 0;
        
        for (int line = 0; line < 2*s + 3; line++)
        {
            for (int j = 0; j < strlen(a); j++)
            {
                printline(a[j], s, line);
                
                if (j != strlen(a) - 1)
                    blankspace(1);
            }
            printf("\n");
        }
        
        //printf ("\n");
    //}
    
    return 0;
}



