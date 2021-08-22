/*  Kenji Yamane                    */
/*  Turma 3                         */
/*                                  */
/*  Exercicio 7: Fibra Ótica        */

/*  CES-11: Algoritmos e Estruturas de Dados
    Prof. Armando
    Dezembro de 2019      */
    
/*  Programa compilado com i686-w64-mingw32-g++*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 11 //maximo de caracteres no nome do predio
#define MAXNOS 150 //maximo de nos
#define MAXARESTAS 2000 //maximo de aresta ida e volta
#define inf 9999 //infinito (o custo maximo de uma aresta eh 1000)

//--------------------------------------------------
//
//    LISTA LIGADA (LAB 1)
//
//--------------------------------------------------

//--------------------------------------------------
//    node's structure
//--------------------------------------------------

struct list
{
    int noFinal;
    int custo;
    struct list *next;
};

typedef struct list linked_list;

//--------------------------------------------------
//    NEW_LIST
//--------------------------------------------------

linked_list *new_list()
{
    return NULL;
}

//--------------------------------------------------
//    CREATE_NODE
//--------------------------------------------------

//node creation
linked_list *create_node(int noFinal, int custo, linked_list *next)
{
    linked_list *l = (linked_list*)malloc(sizeof(linked_list));
    
    if (l != NULL) //if there is enough memory
    {
        //set the parameters to the node
        l->noFinal = noFinal;
        l->custo = custo;
        l->next = next;
    }
    
    return l;
}

//--------------------------------------------------
//    PUSH
//--------------------------------------------------

//inserts a node in the start of the stack
linked_list *push(linked_list *l, int noFinal, int custo)
{
    linked_list *aux = create_node(noFinal, custo, NULL);    
    aux->next = l;
    
    return aux;
}

//--------------------------------------------------
//    DELETE_LIST
//--------------------------------------------------

//frees the stack
void delete_list(linked_list *l)
{
    linked_list *aux;
    
    while (l != NULL)
    {
        aux = l;
        l = l->next;
        free(aux);
    }
}

//--------------------------------------------------
//
//    FILA DE PRIORIDADES POR MIN-HEAP (LAB6)
//
//--------------------------------------------------

//--------------------------------------------------
//    node's structure
//--------------------------------------------------

struct aresta
{
    int prty; //priority
    int noInicial; //starting node
    int noFinal; //node of destiny
};

typedef struct aresta aresta;

//--------------------------------------------------
//    heap's structure ("head node")
//--------------------------------------------------

struct heap
{
    aresta *vector;
    int maxQuantity;
    int quant;
};

//--------------------------------------------------
//    TROCA
//--------------------------------------------------

//troca a informação da posição i com a da posição j de um array t de aresta
//utilizando o algoritmo clássico de troca utilizando atribui
void Troca(aresta *a, int i, int j)
{
    aresta aAux;
    
    aAux.prty = a[i].prty; //prioridade
    aAux.noFinal = a[i].noFinal; //noFinal
    aAux.noInicial = a[i].noInicial; //noInicial
    a[i].prty = a[j].prty;
    a[i].noFinal = a[j].noFinal;
    a[i].noInicial = a[j].noInicial;
    a[j].prty = aAux.prty;
    a[j].noFinal = aAux.noFinal;
    a[j].noInicial = aAux.noInicial;
}

//--------------------------------------------------
//    INICIALIZARHEAP
//--------------------------------------------------

//inicializa a heap h, alocando na heap e setando maxQuantity e quant
heap *InicializarHeap(heap *h, int aux)
{
    h = (heap*)malloc(sizeof(heap)); //alocacao na heap
    
    h->vector = (aresta*)malloc((aux + 1)*sizeof(aresta)); //alocacao na heap
    h->maxQuantity = aux; //setando o valor maximo
    h->quant = 0; //setando a quantidade como 0
    
    return h;
}

//--------------------------------------------------
//    INSERT
//--------------------------------------------------

//insere um node e corrige a propriedade estrutural
void Insert(heap *h, int aux, int noInicial, int noFinal)
{
    h->vector[h->quant + 1].prty = aux; //insere no final o novo node
    h->vector[h->quant + 1].noInicial = noInicial; //para manter o balanceamento
    h->vector[h->quant + 1].noFinal = noFinal; //para manter o balanceamento
    
    //em seguida corrige a propriedade estrutural (enquanto o pai for maior, troca)
    for (int i = h->quant + 1; i != 1 && h->vector[i/2].prty > h->vector[i].prty; i /= 2)
        Troca(h->vector, i, i/2);
    //atualiza quant
    h->quant++;
}

//--------------------------------------------------
//    REMOVEMIN
//--------------------------------------------------

//remove o mínimo da heap
void RemoveMin(heap *h)
{
    h->vector[1].prty = h->vector[h->quant].prty;
    h->vector[1].noInicial = h->vector[h->quant].noInicial;
    h->vector[1].noFinal = h->vector[h->quant].noFinal; //o último passa a ser o primeiro
    bool structural = false; //agora a propriedade estrutural não é mais válida
    int i = 1;
    
    //e em seguida corrige-se a propriedade estrutural
    //a primeira condição corresponde a caso ele tenha chegado no último nível
    while (2*i < h->quant && structural == false)
    {
        int menor;
        
        if (2*i + 1 < h->quant) //se houver os dois filhos, pegue o menor deles
            menor = h->vector[2*i].prty < h->vector[2*i + 1].prty ? 2*i : 2*i + 1;
        else //se houver somente um, este é o esquerdo, e ele que será o menor
            menor = 2*i;
            
        if (h->vector[i].prty > h->vector[menor].prty) //se o pai for menor que o maior deles, faça a troca
        {
            Troca(h->vector, i, menor);
            i = menor;
        }
        else //se o pai for menor que o menor deles, a propriedade estrutural está mantida
            structural = true;
    }
    h->quant--; //atualiza quant
}

//--------------------------------------------------
//    MINIMUM
//--------------------------------------------------

//retorna a raiz, o mínimo
aresta Minimum(heap *h)
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
void FinalizarHeap(heap *h)
{
    free(h->vector);
    free(h);
}

//--------------------------------------------------
//
//    DICIONÁRIO POR VETOR ORDENADO
//
//--------------------------------------------------

//--------------------------------------------------
//    elemento do vetor
//--------------------------------------------------

typedef char cidade[MAX];

struct conta
{
    cidade nome; //nome com no maximo 10 caracteres + \0
};

typedef struct conta conta;

//--------------------------------------------------
//    estrutura gerenciadora
//--------------------------------------------------

struct dicionario
{
    int quant; //quantidade de contas criadas
    int tot; //numero maximo de contas que podem existir simultaneamente
    conta *vetor; //array que guarda a sequencia de informacoes
};

typedef struct dicionario dicionario;

//--------------------------------------------------
//    DICIONARIOVAZIO
//--------------------------------------------------

//indica se o dicionario esta vazia
bool DicionarioVazio(dicionario *d)
{
    //se esta vazia, true, senao, false
    return d->quant == 0 ? true : false;
}

//--------------------------------------------------
//    DICIONARIO CHEIO
//--------------------------------------------------

//indica se a lista esta cheia
bool DicionarioCheio(dicionario *d)
{
    //se esta cheia, true, senao, false
    return d->quant == d->tot ? true : false;
}

//--------------------------------------------------
//    FINALIZARDIC
//--------------------------------------------------

//libera a lista na heap
void FinalizarDic(dicionario *d)
{
    //o ponteiro para vetor
    free(d->vetor);
    //o ponteiro para o gerenciador
    free(d);
}

//--------------------------------------------------
//    INICIALIZARDIC
//--------------------------------------------------

//aloca o espaco necessario e seta os parametros
dicionario *InicializarDic(dicionario *d, int maxim)
{
    d = (dicionario*)malloc(sizeof(dicionario));
    
    d->tot = maxim;
    d->quant = 0;
    d->vetor = (conta*)malloc(d->tot*sizeof(conta));
    
    return d;
}

//--------------------------------------------------
//    BUSCARPOSICAO
//--------------------------------------------------

//Retorna a posicao correspondente a um dado nome, por busca binária
int BuscarPosicao(dicionario *d, const char nome[], int ini, int fim)
{
    if (ini > fim)
        return -1;
    
    //posic tera o valor do meio da lista
    int posic = (ini + fim)/2;
    int found;
    
    //achou o nome ja no meio
    if (strcmp(d->vetor[posic].nome, nome) == 0)
        found = posic;
    //o nome esta a direita
    else if (strcmp(d->vetor[posic].nome, nome) < 0)
        found = BuscarPosicao(d, nome, posic + 1, fim); //procure à direita
    //o nome esta a esquerda
    else if (strcmp(d->vetor[posic].nome, nome) > 0)
        found = BuscarPosicao(d, nome, ini, posic - 1); //procure à esquerda
        
    return found;
}

//--------------------------------------------------
//    BUSCAR
//--------------------------------------------------

//inicializa a busca
int Buscar(dicionario *d, const char nome[])
{
    if (DicionarioVazio(d)) //se a lista estiver vazia, de certeza não há
        return -1;
    
    return BuscarPosicao(d, nome, 0, d->quant);
}

//--------------------------------------------------
//    INSERIR
//--------------------------------------------------

//insere um elemento na lista
void Inserir(dicionario *d, const char nome[])
{
    int i;
    
    //enquanto não estiver na posição correta, realize o shift
    for (i = d->quant; i > 0 && strcmp(d->vetor[i - 1].nome, nome) > 0; i--)
        strcpy(d->vetor[i].nome, d->vetor[i - 1].nome);
    strcpy(d->vetor[i].nome, nome); //insira na posição liberada
    d->quant++; //atualizando a quantidade
}

//--------------------------------------------------
//    RETORNARNOME
//--------------------------------------------------

void retornarNome(dicionario *d, int indice, cidade recebe)
{
    strcpy(recebe, d->vetor[indice].nome);
}

//--------------------------------------------------
//
//    GRAFO
//
//--------------------------------------------------

typedef linked_list* listaLigada;

//--------------------------------------------------
//    estrutura gerenciadora
//--------------------------------------------------

struct grafo
{
    listaLigada vetorListas[MAXNOS]; //vetor de listas ligadas
};

typedef struct grafo grafo;

//--------------------------------------------------
//    INICIALIZARGRAFO
//--------------------------------------------------

//seta as listas ligadas do grafo
grafo *inicializarGrafo(grafo *g, int tam)
{
    g = (grafo*)malloc(sizeof(grafo)); //aloca na heap
    
    for (int i = 0; i < tam; i++)
        g->vetorListas[i] = NULL; //inicializa as listas
        
    return g;
}

//--------------------------------------------------
//    INSERIRARESTA
//--------------------------------------------------

void inserirAresta(grafo *g, int noPartida, int noTermino, int custo) //o grafo é não-direcionado
{
    g->vetorListas[noPartida] = push(g->vetorListas[noPartida], noTermino, custo); //insere numa direção
    g->vetorListas[noTermino] = push(g->vetorListas[noTermino], noPartida, custo); //e na outra
}

//--------------------------------------------------
//    FINALIZARGRAFO
//--------------------------------------------------

//libera na heap
void finalizarGrafo(grafo *g, int tam)
{
    for (int i = 0; i < tam; i++)
        delete_list(g->vetorListas[i]); //libera cada lista da memoria
    
    free(g); //libera a estrutura gerenciadora
}

//--------------------------------------------------
//
//    MAIN
//
//--------------------------------------------------

int main()
{
    FILE *e = fopen("C:\\Lab7\\entrada7.txt", "r");
    FILE *s = fopen("C:\\Lab7\\kenjiyamane7.txt", "w");
    dicionario *d = NULL; //dicionario para traduzir de palavras para numeros
    grafo *g = NULL; //o grafo em si
    heap *h = NULL; //heap para ser usado no Prim
    heap *hsaida = NULL; //heap para imprimir ordenado por custo
    int custo, custoTotal, dist[MAXNOS];
    cidade nome1, nome2;
    char lixo[72];
    bool incluso[MAXNOS];
    
    for (int i = 0; i < MAXNOS; i++)
        dist[i] = inf; //inicializando com infinito
    memset(incluso, false, sizeof(incluso)); //nenhum no incluso no MST
    d = InicializarDic(d, MAXNOS); //inicializando dicionario com o maximo de nohs
    g = inicializarGrafo(g, MAXNOS); //inicializando grafo com o maximo de nohs
    h = InicializarHeap(h, MAXARESTAS); //inicializando heap com o maximo de arestas
    hsaida = InicializarHeap(hsaida, MAXARESTAS); //idem ao de cima
    
    for (int i = 0; i < 6; i++) //Primeiras seis linhas contém lixo
        fgets(lixo, 72, e);
    
    //construindo o dicionário
    while (fscanf(e, "%s %s %*d\n", nome1, nome2) != EOF)
    {
        if (Buscar(d, nome1) == -1) //se não existir no dicionário
            Inserir(d, nome1); //insira
        if (Buscar(d, nome2) == -1) //se não existir no dicionário
            Inserir(d, nome2); //insira
    }
    
    fseek(e, 0, SEEK_SET); //retorno do ponteiro de arquivo para o inicio
    for (int i = 0; i < 6; i++) //Primeiras seis linhas contém lixo
        fgets(lixo, 72, e);
    
    //construindo o grafo
    while (fscanf(e, "%s %s %d\n", nome1, nome2, &custo) != EOF)
        inserirAresta(g, Buscar(d, nome1), Buscar(d, nome2), custo); //inserir aresta
    
    //implementação do algoritmo de Prim
    incluso[0] = true; //comecando pelo primeiro
    dist[0] = 0; //sua distancia eh 0
    custoTotal = 0;
    for (listaLigada l = g->vetorListas[0]; l != NULL; l = l->next) //adicione todos os seus vizinhos na heap
        if (l->custo < dist[l->noFinal]) //se for menor que o valor tabelado
        {
            dist[l->noFinal] = l->custo; //atualize o valor
            Insert(h, l->custo, 0, l->noFinal); //insira na heap
        }
    
    fprintf(s, "500 linhas de códigooo\n");
    fprintf(s, "não sabia se o erro tava na heap, na lista ligada, no grafo\n");
    fprintf(s, "falta soh mais um lab pra eu poder usar c++ e POO hehehe\n\n");
    
    fprintf(s, "---------------------------------------\n");
    fprintf(s, "Ordem de seleção pelo algoritmo\n");
    fprintf(s, "---------------------------------------\n");
    
    while (!HeapVazio(h))
    {
        //o noh final de menor custo eh inserido na MST, entao
        retornarNome(d, Minimum(h).noInicial, nome1); //retorna-se o noh de comeco da aresta
        retornarNome(d, Minimum(h).noFinal, nome2); //o noh de fim
        fprintf(s, "%-10s %-10s %3d\n", nome1, nome2, Minimum(h).prty); //e imprime-os no arquivo
        Insert(hsaida, Minimum(h).prty, Minimum(h).noInicial, Minimum(h).noFinal); //e insere na heap de saida a ser ordenada
        custoTotal += Minimum(h).prty; //atualiza-se o custo total
        incluso[Minimum(h).noFinal] = true; //e o inclui na MST
        
        int noFinal = Minimum(h).noFinal; //marca-se o no final de menor custo
        for (listaLigada l = g->vetorListas[noFinal]; l != NULL; l = l->next) //e analisa todos os seus vizinhos
            if (l->custo < dist[l->noFinal]) //os que tiverem distância menor que o tabelado
            {
                dist[l->noFinal] = l->custo; //atualiza-se a distancia
                Insert(h, l->custo, noFinal, l->noFinal); //e insere na heap
            }
        
        while (!HeapVazio(h) && incluso[Minimum(h).noFinal] == true) //retira-se da heap aqueles que ja estao no MST
            RemoveMin(h);
    }
    fprintf(s, "\nCusto total: %d\n\n", custoTotal);
    fprintf(s, "---------------------------------------\n");
    fprintf(s, "Ordem crescente de custos\n");
    fprintf(s, "---------------------------------------\n");
    while (!HeapVazio(hsaida)) //agora para imprimir em ordem de custo
    {
        retornarNome(d, Minimum(hsaida).noInicial, nome1);
        retornarNome(d, Minimum(hsaida).noFinal, nome2);
        fprintf(s, "%-10s %-10s %3d\n", nome1, nome2, Minimum(hsaida).prty);
        RemoveMin(hsaida);
    }
    
    FinalizarDic(d); //liberando dicionario
    finalizarGrafo(g, MAXNOS); //liberando grafo
    FinalizarHeap(h); //liberando heap
    FinalizarHeap(hsaida); //liberando a heap de saida
    fclose(e);
    fclose(s);
    
    return 0;
}
