/*  Kenji Yamane                    */
/*  Turma 3                         */
/*                                  */
/*  Exercicio 3: Ordenação          */

/*  CES-11: Algoritmos e Estruturas de Dados
    Prof. Armando
    Setembro de 2019      */
    
/*  Programa compilado com o compilador g++*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*Nota importante: Estou ciente de que o strcmp é case insensitive, ou seja*/
/*ele não leva em consideração a diferença entre upper-case e lower-case, e*/
/*os compara como números, o que acaba por gerar erros, considerando todas */
/*as letras maiúsculas como anteriores às letras minúsculas por serem      */
/*menores na tabela ASCII. Porém como são nomes de pessoas, é pressuposto  */
/*que todo nome começa com letra maiúscula, e o resto é minúsculo. Assim   */
/*não há comparações entre maiúsculos e minúsculos e portanto isso não foi */
/*considerado nesse código.                                                */

#define MAX 52 //os 50 previstos mais o término de string mais o \n
int contador; //conta o número de comparações
int counter;

//--------------------------------------------------
//    tipo do vetor
//--------------------------------------------------

typedef char tipelemento[MAX];
typedef tipelemento* vetor;

//--------------------------------------------------
//    COMPARA
//--------------------------------------------------

//função feita para extender a comparação em virtude to tipelemento ser string
int compara (const char *a, const char *b)
{
    contador++; //cálculo do número de comparações
    return strcmp(a, b);
}

//--------------------------------------------------
//    BUBBLE SORT
//--------------------------------------------------

/*
No laço mais interno, o maior é levado até o final
comparando e retificando os elementos de dois a dois.
No laço externo, isso é feito N - 1 vezes, sempre para
levar o maior ao final do vetor ainda não ordenado
*/
void BubbleSort(vetor V, int ini, int fim)
{
    tipelemento aux;
    
    for (int i = fim; i > ini; i--) // laço externo
        for (int j = ini + 1; j <= i; j++) // laço interno
            if (compara(V[j - 1], V[j]) > 0) //se estiver desordenado, execute a troca
            {
                strcpy(aux, V[j - 1]);
                strcpy(V[j - 1], V[j]);
                strcpy(V[j], aux);
            }
}

//--------------------------------------------------
//    MERGE
//--------------------------------------------------
/*
Dado um vetor V e dadas duas posicoes ini e fim.
A metade da esquerda desse trecho jaŽ estaŽ ordenada e
a metade da direita  desse trecho jaŽ estaŽ ordenada.
Fazer intercalacao (merge) e obter V ordenado.
*/

vetor T;

void Merge (vetor V, int ini, int fim)
{
    counter++;
    int med,
        i,     // percorre T
        j,     // percorre lado esquerdo de V
        k;     // percorre lado direito  de V
    
    med = (ini+fim)/2; //mesmo arredondamento feito ao chamar MergeSort
    j = ini;
    k = med+1;
    i = ini;
    //percorrer selecionando os menores
    while (j <= med && k <= fim)
    {
        if (compara(V[j], V[k]) <= 0)
        {
            strcpy(T[i], V[j]);
            j++;
        }
        else
        {
            strcpy(T[i], V[k]);
            k++;
        }
        i++;
    }
    //se sobrou algo `a esquerda, copiar para T
    while(j <= med)
    {
        strcpy(T[i], V[j]);
        i++;
        j++;
    }
    //se sobrou algo `a direita, copiar para T
    while(k<=fim)
    {
        strcpy(T[i], V[k]);
        i++;
        k++;
    }
    // V recebe T
    for(i=ini; i<=fim; i++)
        strcpy(V[i], T[i]);
}

//--------------------------------------------------
//    MERGE SORT
//--------------------------------------------------

void MergeSort (vetor V, int ini, int fim)
{
    int med;
    if (ini < fim)
    {
        med = (ini+fim)/2;          // dividir ao meio
        MergeSort (V, ini,   med);  // ordenar lado esquerdo
        MergeSort (V, med+1, fim);  // ordenar lado direito
        Merge     (V, ini,   fim);  // mesclar as duas metades
    }
}

//--------------------------------------------------
//    PARTITION
//--------------------------------------------------
/*
Dado um vetor V com elementos em qualquer ordem,
escolher um elemento para ser pivo^
e então dividir os elementos de V em duas partes:
  `a esquerda: menores que o pivo
  `a direita:  maiores ou iguais ao pivo
*/

int Partition (vetor V, int ini, int fim)
{
    tipelemento pivo, aux;
    int esq, dir;

    strcpy(pivo, V[ini]);    // neste exemplo, o pivo é o primeiro da esquerda
    esq  = ini + 1;
    dir  = fim;
    do
    {
        // percorrer da esquerda para a direita. encontrar alguem >= pivo
        while (esq < fim && compara(V[esq], pivo) < 0)
            esq++;
        // percorrer da direita para a esquerda. encontrar alguem < pivo
        while (ini < dir && compara(pivo, V[dir]) <= 0)
            dir--;
        // se achou um `a esquerda e outro `a direita
        if(esq < dir)
        {
            // permutar
            strcpy(aux, V[esq]);
            strcpy(V[esq], V[dir]);
            strcpy(V[dir], aux);
        }
        // caso contrario, terminaraŽ a repeticao
    }while (esq < dir);

    // trocar o pivo com o elemento que "divide" os subvetores
    strcpy(V[ini], V[dir]);
    strcpy(V[dir], pivo);
    // retornar a posição da "divisa"
    return dir;
}

//--------------------------------------------------
//    QUICK SORT
//--------------------------------------------------

void QuickSort (vetor V, int ini, int fim)
{
    int p; //posição do pivo
    if (ini < fim)
    {
        p = Partition (V, ini, fim);
        QuickSort     (V, ini, p-1);
        QuickSort     (V, p+1, fim);
    }
}

//--------------------------------------------------
//    MAIN
//--------------------------------------------------

int main()
{
    FILE *e = fopen(/*"C:\\Lab3\\*/"entrada3.txt", "r");
    FILE *bubble_s = fopen(/*"C:\\Lab3\\*/"kenjiyamane3bubble.txt", "w");
    FILE *merge_s = fopen(/*"C:\\Lab3\\*/"kenjiyamane3merge.txt", "w");
    FILE *quick_s = fopen(/*"C:\\Lab3\\*/"kenjiyamane3quick.txt", "w");
    
    int N, i;
    clock_t ini, fim; //variáveis para marcar tempo
    
    //inicio da entrada; não entrará na contagem do tempo
    fscanf(e, "%d%*c", &N); //%*c lerá o enter após o número
    
    //arrays de strings para cada um dos algoritmos de ordenação
    vetor nomes_bubble = (vetor)malloc(N*sizeof(tipelemento));
    vetor nomes_merge = (vetor)malloc(N*sizeof(tipelemento));
    vetor nomes_quick = (vetor)malloc(N*sizeof(tipelemento));
    T = (vetor)malloc(N*sizeof(tipelemento));   // temporario
    for (i = 0; i < N; i++)
    {
        fgets(nomes_bubble[i], MAX, e);
        strcpy(nomes_merge[i], nomes_bubble[i]);
        strcpy(nomes_quick[i], nomes_merge[i]);
    }
    printf("%s", nomes_bubble[N - 1]);
    //fim da entrada
    
    //gerando o arquivo de bubble sort
    contador = 0;
    
    ini = clock();
    BubbleSort(nomes_bubble, 0, N - 1);
    fim = clock();
    
    fprintf(bubble_s, "Algoritmo: Bubble-Sort\n\n");
    fprintf(bubble_s, "Tamanho da entrada: %d\n", N);
    fprintf(bubble_s, "Comparações feitas: %d\n", contador);
    fprintf(bubble_s, "Tempo de execução : %.3f segundos\n\n", (float)((fim - ini)/CLOCKS_PER_SEC));
    for (i = 0; i < N; i++)
        fprintf(bubble_s, "%s", nomes_bubble[i]);
    
    //gerando o arquivo de merge sort
    contador = 0;
    
    ini = clock();
    MergeSort(nomes_merge, 0, N - 1);
    fim = clock();
    
    fprintf(merge_s, "Algoritmo: Bubble-Sort\n\n");
    fprintf(merge_s, "Tamanho da entrada: %d\n", N);
    fprintf(merge_s, "Comparações feitas: %d\n", contador);
    fprintf(merge_s, "Tempo de execução : %.3f segundos\n\n", (float)((fim - ini)/CLOCKS_PER_SEC));
    for (i = 0; i < N; i++)
        fprintf(merge_s, "%s", nomes_merge[i]);
    
    //gerando o arquivo de quick sort
    contador = 0;
    
    ini = clock();
    QuickSort(nomes_quick, 0, N - 1);
    fim = clock();
    
    fprintf(quick_s, "Algoritmo: Bubble-Sort\n\n");
    fprintf(quick_s, "Tamanho da entrada: %d\n", N);
    fprintf(quick_s, "Comparações feitas: %d\n", contador);
    fprintf(quick_s, "Tempo de execução : %.3f segundos\n\n", (float)((fim - ini)/CLOCKS_PER_SEC));
    for (i = 0; i < N; i++)
        fprintf(quick_s, "%s", nomes_quick[i]);
    
    //liberando espaço de memória
    free(nomes_bubble);
    free(nomes_merge);
    free(nomes_quick);
    free(T);
    printf("%d\n", counter);
    //fechando os arquivos
    fclose(e);
    fclose(bubble_s);
    fclose(merge_s);
    fclose(quick_s);
    
    return 0;
}
