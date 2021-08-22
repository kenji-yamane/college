/***********************************/
/* Aluno: Kenji Yamane             */
/* CES-10: Introdução à Computação */
/* Prof. Victor Curtis             */
/***********************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define Candidate struct Competitor

Candidate
{
    char name[81];
    int votes;
    bool victorious;
    bool declassified;
};

void InitializeCandidates (Candidate* candidates, int Ncand)
{
    for (int i = 0; i < Ncand; i++)
    {
        scanf (" %[^\n]s", (candidates + i) -> name);
        (candidates + i) -> victorious = false;
        (candidates + i) -> declassified = false;
        (candidates + i) -> votes = 0;
    }
}

bool verifyEnding (Candidate* candidates, int Ncand)
{
    int i, pivot = 0;
    
    for (i = 0; i < Ncand && pivot == 0; i++)
        if ((candidates + i) -> declassified == false)
            pivot = (candidates + i) -> votes;
            
    for (i = 0; i < Ncand; i++)
        if ((candidates + i) -> declassified == false)
            if ((candidates + i) -> votes != pivot)
                return false;
                
    return true;
}

void eliminateCandidates (Candidate* candidates, int Nball, int Ncand)
{
    int i, min = Nball + 1;
    
    for (i = 0; i < Ncand; i++)
        if ((candidates + i) -> declassified == false)
            if ((candidates + i) -> votes < min)
                min = (candidates + i) -> votes;
                
    for (i = 0; i < Ncand; i++)
        if ((candidates + i) -> declassified == false)
            if ((candidates + i) -> votes == min)
                (candidates + i) -> declassified = true;
                
    return;
}

void cleanBallots (int** ballots, Candidate* candidates, int Nball)
{ 
    for (int i = 0; i < Nball; i++)
        if ((candidates + **(ballots + i) - 1) -> declassified == true)
            (*(ballots + i))++;
            
    for (int i = 0; i < Nball; i++)
        if ((candidates + **(ballots + i) - 1) -> declassified == true)
            cleanBallots (ballots, candidates, Nball);
}

void revertPointers (int** ballots, int Nball, int* originalTops)
{
    for (int i = 0; i < Nball; i++)
    {
        while ((**(ballots + i)) != *(originalTops + i))
            (*(ballots + i))--;
    }
}

void analyzeVictory (int** ballots, Candidate* candidates, int Nball, int Ncand)
{   
    for (int i = 0; i < Ncand; i++)
        (candidates + i) -> votes = 0;
    for (int i = 0; i < Nball; i++)
        (candidates + **(ballots + i) - 1) -> votes++;

    int max = 0;
    for (int i = 0; i < Ncand; i++)
        if ((candidates + i) -> declassified == false)
            if ((candidates + i) -> votes > max)
                max = (candidates + i) -> votes;
                
    if ((float)max/Nball > 0.5)
    {
        for (int i = 0; i < Ncand; i++)
            if ((candidates + i) -> declassified == false)
                if ((candidates + i) -> votes == max)
                    (candidates + i) -> victorious = true;
                
        return;
    }
    
    if (verifyEnding (candidates, Ncand) == true)
    {
        for (int i = 0; i < Ncand; i++)
            if ((candidates + i) -> declassified == false)
                (candidates + i) -> victorious = true;
        
        return;
    }
    
    eliminateCandidates (candidates, Nball, Ncand); 
    cleanBallots (ballots, candidates, Nball);    
    analyzeVictory (ballots, candidates, Nball, Ncand);
}

int main ()
{
    int N, Ncand, Nball, i, j;
    char eater[5];
    
    scanf ("%d\n\n", &N);
    
    for (i = 0; i < N; i++)
    {
        int verify = 0;
        int **ballots;
        int *originalTops;
        Candidate *candidates;
        
        scanf ("%d", &Ncand);
        candidates = (Candidate*)malloc (Ncand*sizeof (Candidate));
        ballots = (int**)malloc (sizeof (int*));
        
        InitializeCandidates (candidates, Ncand);
        
        for (Nball = 0; verify != 2; Nball++)
        {
            *(ballots + Nball) = (int*)malloc (Ncand*sizeof (int));
            
            for (j = 0; j < Ncand; j++)
                scanf ("%d", (*(ballots + Nball) + j));
            
            if (scanf ("%[^1-9]", eater) == EOF)
                break;
                
            verify = strlen (eater);
            
            if (verify != 2)
                ballots = (int**)realloc (ballots, (Nball + 2)*sizeof (int*));
        }
        
        originalTops = (int*)malloc (Nball*sizeof (int));
        
        for (j = 0; j < Nball; j++)
            *(originalTops + j) = **(ballots + j);
        
        analyzeVictory (ballots, candidates, Nball, Ncand);
        
        for (j = 0; j < Ncand; j++)
            if ((candidates + j) -> victorious == true)
                printf ("%s\n", (candidates + j) -> name);
        if (i != N - 1)
            printf ("\n");
        
        revertPointers (ballots, Nball, originalTops);
        free (candidates);
        for (j = 0; j < Nball; j++)
            free (*(ballots + j));
        free (ballots);
        free (originalTops);
    }
    
    return 0;
}




