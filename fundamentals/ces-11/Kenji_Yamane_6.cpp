/*  Kenji Yamane                    */
/*  Turma 3                         */
/*                                  */
/*  Exercicio 6: Agenda Eletrônica  */

/*  CES-11: Algoritmos e Estruturas de Dados
    Prof. Armando
    Novembro de 2019      */
    
/*  Programa compilado com i686-w64-mingw32-g++*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//--------------------------------------------------
//    node's structure
//--------------------------------------------------

struct task
{
    int prty; //priority
    char description[72];
};

typedef struct task task;

//--------------------------------------------------
//    heap's structure ("head node")
//--------------------------------------------------

struct heap
{
    task *vector;
    int maxQuantity;
    int quant;
};

//--------------------------------------------------
//    TROCA
//--------------------------------------------------

//troca a informação da posição i com a da posição j de um array t de tasks
//utilizando o algoritmo clássico de troca (porém para cada elemnto da struct)
void Troca(task *t, int i, int j)
{
    task tAux;
    
    tAux.prty = t[i].prty;
    strcpy(tAux.description, t[i].description);
    t[i].prty = t[j].prty;
    strcpy(t[i].description, t[j].description);
    t[j].prty = tAux.prty;
    strcpy(t[j].description, tAux.description);
}

//--------------------------------------------------
//    INICIALIZAR
//--------------------------------------------------

//inicializa a heap h, alocando na heap e setando maxQuantity e quant
heap *Inicializar(heap *h, int aux)
{
    h = (heap*)malloc(sizeof(heap)); //alocacao na heap
    
    h->vector = (task*)malloc((aux + 1)*sizeof(task)); //alocacao na heap
    h->maxQuantity = aux; //setando o valor maximo
    h->quant = 0; //setando a quantidade como 0
    
    return h;
}

//--------------------------------------------------
//    INSERT
//--------------------------------------------------

//insere um node e corrige a propriedade estrutural
void Insert(heap *h, int aux, char description[])
{
    h->vector[h->quant + 1].prty = aux; //insere no final o novo node
    strcpy(h->vector[h->quant + 1].description, description); //para manter o balanceamento
    
    //em seguida corrige a propriedade estrutural (enquanto o pai for menor, troca)
    for (int i = h->quant + 1; i != 1 && h->vector[i/2].prty < h->vector[i].prty; i /= 2)
        Troca(h->vector, i, i/2);
    //atualiza quant
    h->quant++;
}

//--------------------------------------------------
//    REMOVEMAX
//--------------------------------------------------

//remove o máximo da heap
void RemoveMax(heap *h)
{
    h->vector[1].prty = h->vector[h->quant].prty;
    strcpy(h->vector[1].description, h->vector[h->quant].description); //o último passa a ser o primeiro
    bool structural = false; //agora a propriedade estrutural não é mais válida
    int i = 1;
    
    //e em seguida corrige-se a propriedade estrutural
    //a primeira condição corresponde a caso ele tenha chegado no último nível
    while (2*i < h->quant && structural == false)
    {
        int maior;
        
        if (2*i + 1 < h->quant) //se houver os dois filhos, pegue o maior deles
            maior = h->vector[2*i].prty > h->vector[2*i + 1].prty ? 2*i : 2*i + 1;
        else //se houver somente um, este é o esquerdo, e ele que será o maior
            maior = 2*i;
            
        if (h->vector[i].prty < h->vector[maior].prty) //se o pai for menor que o maior deles, faça a troca
        {
            Troca(h->vector, i, maior);
            i = maior;
        }
        else //se o pai for maior que o maior deles, a propriedade estrutural está mantida
            structural = true;
    }
    h->quant--; //atualiza quant
}

//--------------------------------------------------
//    MAXIMUM
//--------------------------------------------------

//retorna a raiz, o máximo
task Maximum(heap *h)
{
    return h->vector[1];
}

//--------------------------------------------------
//    HEAPVAZIO
//--------------------------------------------------

//retorna se esta vazio
bool HeapVazio(heap *h)
{
    return (h->quant == 0);
}

//--------------------------------------------------
//    HEAPCHEIO
//--------------------------------------------------

//retorna se esta cheio
bool HeapCheio(heap *h)
{
    return (h->quant == h->maxQuantity);
}

//--------------------------------------------------
//    FINALIZAR
//--------------------------------------------------

//libera o espaco na heap
void Finalizar(heap *h)
{
    free(h->vector);
    free(h);
}

//--------------------------------------------------
//    MAIN
//--------------------------------------------------

int main()
{
    FILE *e = fopen("C:\\Lab6\\entrada6.txt", "r");
    FILE *s = fopen("C:\\Lab6\\kenjiyamane6.txt", "w");
    
    heap *h = NULL;
    char line[72], description[72], command[8];
    int aux;
    
    //first five lines wont't be processed
    for (int i = 0; i < 5; i++)
        fgets(line, 72, e);
    fscanf(e, "%d\n", &aux);
    
    h = Inicializar(h, aux);
    
    //next three lines won't be processed
    for (int i = 0; i < 3; i++)
        fgets(line, 72, e);
    
    //first 5 lines are livressss
    fprintf(s, "Uma vez um monge estava meditando sobre as montanhas\n");
    fprintf(s, "e então começou a sonhar que era uma borboleta.\n");
    fprintf(s, "Ao retornar o monge já não sabia mais dizer\n");
    fprintf(s, "se era homem que estava sonhando ser borboleta\n");
    fprintf(s, "ou se era borboleta que agora sonha em ser homem\n");
    fprintf(s, "--------------------------------------------------\n");
    fprintf(s, "RESPOSTAS DAS CONSULTAS\n");
    fprintf(s, "--------------------------------------------------\n");
    
    do
    {
        fscanf(e, " %s", command);
        
        if (strcmp(command, "NOVA") == 0) //para inserir nova atividade
        {
            fscanf(e, "%d ", &aux);
            fgets(description, 72, e);
            
            if (HeapCheio(h)) //se estiver cheio não é possivel inserir nova atividade
                fprintf(s, "ERRO     SUGOU!\n");
            else
                Insert(h, aux, description); // senao insere
        }
        else if (strcmp(command, "PROXIMA") == 0) //para verificar a proxima atividade
        {
            if (HeapVazio(h)) //se estiver vazio, não novas atividades
                fprintf(s, "AVISO    sem tarefas pra amanhã (coçou!)\n");
            else //senao expoe o topo e remove
            {
                fprintf(s, "%2d       %s", Maximum(h).prty, Maximum(h).description);
                RemoveMax(h);
            }
        }
    } while (strcmp(command, "FIM") != 0);
    
    fprintf(s, "\n");
    fprintf(s, "--------------------------------------------------\n");
    fprintf(s, "FICA PARA O DIA SEGUINTE\n");
    fprintf(s, "--------------------------------------------------\n");
    if (HeapVazio(h)) // caso em que nao tem mais atividade
        fprintf(s, "AVISO: da pra ir pro all-night amanha\n");
    while (!HeapVazio(h)) //se tiver, immprime todas as que restam em ordem
    {
        fprintf(s, "%2d       %s", Maximum(h).prty, Maximum(h).description);
        RemoveMax(h);
    }
    
    Finalizar(h); //libera a memoria da heap
    
    return 0;
}
