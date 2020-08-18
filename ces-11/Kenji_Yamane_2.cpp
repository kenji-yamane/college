/*  Kenji Yamane                    */
/*  Turma 3                         */
/*                                  */
/*  Exercicio 1: Torre de Controle  */

/*  CES-11: Algoritmos e Estruturas de Dados
    Prof. Armando
    Setembro de 2019      */
    
/*  Programa compilado com o compilador g++ e a flag -fsanitize=leak,address,undefined*/

#include <stdio.h>
#include <string.h>


int pivot[21][21]; //[i][j] stores the best division for the sequence of matrixes of i to j
int rec_count = 0; //counts the number of recursion calls

/*--------------------------------------------------*/
//return the best division for the sequence of matrixes of i to j
int OptMult(int ini, int fim, int mtx[20][2])
{
    int subprob; //stores the best solution for one division
    int ans = -1; //stores the minimum of subprob
    
    rec_count++;
    //i is the division, or "cut" to be made
    for (int i = ini; i < fim - 1; i++)
    {
        //determination of the best multiplication for such i
        subprob = mtx[ini][0]*mtx[i][1]*mtx[fim - 1][1] + OptMult(ini, i + 1, mtx) + OptMult(i + 1, fim, mtx);
        //begin of minimum search algorithm
        if (ans == -1 || ans > subprob)
        {
            ans = subprob;
            //storage for the pivot[][]
            pivot[ini][fim] = i;
        }
        //end of minimum search algorithm
    }
    
    return ans == -1 ? 0 : ans;
}

/*--------------------------------------------------*/
//using the values stored in pivot[][], prints the solutions, giving priority to the left
void print_optimal(int ini, int fim, int mtx[20][2], FILE *s)
{
    if (pivot[ini][fim] != -1) //if pivot is -1, then it is the end, because it hasn't been touched
    {
        //print the left
        print_optimal(ini, pivot[ini][fim] + 1, mtx, s);
        //print the right
        print_optimal(pivot[ini][fim] + 1, fim, mtx, s);
        
        //print the multiplication between the left and the right
        if (pivot[ini][fim] == ini) //left is only one matrix
            fprintf(s, "   %2d x ", ini + 1);
        else //left is more than one matrix
            fprintf(s, "%2d-%2d x ", ini + 1, pivot[ini][fim] + 1);
        if (fim - pivot[ini][fim] == 2) //right is only one number
            fprintf(s, "%2d\n", fim);
        else //right is more than one number
            fprintf(s, "%2d-%2d\n", pivot[ini][fim] + 2, fim);
    }
}

/*--------------------------------------------------*/

int main()
{
    FILE *e = fopen("C:\\Lab2\\entrada2.txt", "r");
    FILE *s = fopen("C:\\Lab2\\kenjiyamane2.txt", "w");
    
    int N, i;
    int mtx[20][2]; //[i][0] is line and [i][1] is collumn of matrix i
    char lixo[100];
    
    //first five lines of input
    for (i = 0; i < 5; i++)
        fgets(lixo, 100, e);
    fscanf(e, "%d ", &N);
    fgets(lixo, 100, e);
    for (i = 0; i < N; i++)
        fscanf(e, "%d %d", &mtx[i][0], &mtx[i][1]);
    
    //setting all values of pivot to -1
    memset(pivot, -1, sizeof(pivot));
    
    fprintf(s, "Exemplo de arquivo de saida\n");
    fprintf(s, "Exercicio 2\n");
    fprintf(s, "Produto de Matrizes\n\n");
    fprintf(s, "Total de multiplicacoes escalares = %d\n\n", OptMult(0, N, mtx));
    fprintf(s, "Chamadas aa funcao: %d\n\n", rec_count);
    fprintf(s, "Melhor ordem para realizar o produto:\n");
    print_optimal(0, N, mtx, s);
    
    fclose(s);
    fclose(e);
    
    return 0;
}
