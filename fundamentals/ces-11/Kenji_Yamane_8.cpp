/*  Kenji Yamane                    */
/*  Turma 3                         */
/*                                  */
/*  Exercicio 8: PERT               */

/*  CES-11: Algoritmos e Estruturas de Dados
    Prof. Armando
    Dezembro de 2019      */
    
/*  Programa compilado com i686-w64-mingw32-g++*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define inicio 52
#define inf 99999999


//--------------------------------------------------
//
//    PILHA POR LISTA LIGADA
//
//--------------------------------------------------

//--------------------------------------------------
//    estrutura do noh
//--------------------------------------------------

struct pilha
{
    int info; //conteudo do noh, um inteiro
    struct pilha *next; //ponteiro para o proximo
};

typedef struct pilha pilha;

//--------------------------------------------------
//    CREATE_NODE
//--------------------------------------------------

//cria um noh de inteiro info e cujo proximo eh next
pilha *create_node(int info, pilha *next)
{
    pilha *p = (pilha*)malloc(sizeof(pilha)); //alocacao na heap
    
    p->info = info; //setando info
    p->next = next; //setando next
    
    return p;
}

//--------------------------------------------------
//    PUSH
//--------------------------------------------------

//insere um noh na pilha
pilha *push(pilha *p, int novaInfo)
{
    return create_node(novaInfo, p); //cria e o novo primeiro eh o criado
}

//--------------------------------------------------
//    TOP
//--------------------------------------------------

//retorna o inteiro no topo da filha
int top(pilha *p)
{
    return p->info;
}

//--------------------------------------------------
//    POP
//--------------------------------------------------

//elimina um node da pilha, de cima
pilha *pop(pilha *p)
{
    pilha *aux = p->next; //auxiliar que sera o novo primeiro
    free(p); //apaga o antigo primeiro
    return aux;
}

//--------------------------------------------------
//
//    VARIÁVEIS GLOBAIS
//
//--------------------------------------------------

int pivot, //variavel de manipulacao de dados
    grafo[53][53], //matriz de adjacencias
    caminhoCiclo[53]; //array que guarda os parentes num ciclo
bool ciclico, //booleana que diz se eh ciclico ou n
     ancestral[53], //array de ancestrais do algoritmo de ciclos
     visited[53]; //array que diz se um no foi visitado ou n
pilha *p, //pilha para ancestrais no algoritmo de ordenacao topologica
      *ordemTopologica; //usada para inverter a saida da pilha p

//--------------------------------------------------
//
//    FUNCOES DO GRAFO POR MATRIZ DE ADJACENCIAS
//
//--------------------------------------------------

//--------------------------------------------------
//    DICIONARIO
//--------------------------------------------------

//realiza transformacao biunivoca das 52 letras para os inteiros de 0 a 51
int dicionario(char a)
{
    if (a >= 'a' && a <= 'z')
        return (int)(a - 'a'); //'a' a 'z' vira de 0 a 25
    else
        return (int)(a - 'A' + 'z' - 'a' + 1); //'A' a 'Z' vira de 26 a 51
}

//--------------------------------------------------
//    RETORNO
//--------------------------------------------------

//funcao inversa da dicionario
char retorno(int a)
{
    if (a < 26)
        return (char)a + 'a'; //0 a 25 vira de 'a' a 'z'
    else
        return (char)a - 26 + 'A'; //26 a 51 vira de 'A' a 'Z'
}

//--------------------------------------------------
//    DEPTHFIRSTSEARCH
//--------------------------------------------------

//algoritmo de busca em profundidade, com marcador de visitado e marcador de ancestral
void depthFirstSearch(int source)
{
    ancestral[source] = true; //ancestral
    visited[source] = true; //visitado
    
    for (int i = 0; i < 53 && ciclico == false; i++)
        if (grafo[source][i] < inf && ancestral[i] == false && visited[i] == false) //se n for nem ancestral nem visitado
        {
            depthFirstSearch(i); //acesse recursivamente
            caminhoCiclo[source] = i; //guarde o pai para caso seja achado ciclo vinculado a source
        }
        else if (grafo[source][i] < inf && ancestral[i] == true) //se houver aresta e for ancestral, ha ciclo
        {
            ciclico = true; //seta como true
            caminhoCiclo[source] = i; //finaliza o ciclo setando seu pai
            pivot = i; //guarda um noh do ciclo em pivot
        }
    
    ancestral[source] = false; //deixa de ser ancestral
}

//--------------------------------------------------
//    ORDENACAOTOPOLOGICA
//--------------------------------------------------

//algoritmo de determinacao da ordem topologica, com marcador de visitado e pilha de ancestrais
void ordenacaoTopologica(int source)
{
    visited[source] = true; //visitado
    
    if (source != inicio)
        p = push(p, source); //insere na pilha de ancestrais
    
    for (int i = 0; i < 53; i++)
        if (grafo[source][i] < inf && visited[i] == false) //se aresta existir e nao tiver sido visitado
            ordenacaoTopologica(i); //acesse recursivamente
    
    if (source != inicio)
    {
        ordemTopologica = push(ordemTopologica, top(p)); //insercao da pos-ordem inversa
        p = pop(p); //retira da pilha de ancestrais
    }
}

//--------------------------------------------------
//
//    MAIN
//
//--------------------------------------------------

int main()
{
    FILE *e = fopen("C:\\Lab8\\entrada8.txt", "r");
    FILE *s = fopen("C:\\Lab8\\kenjiyamane8.txt", "w");
    char rotulo, //identificador da tarefa
         lixo[72], //string que guarda aas frases iniciais
         carac, //ler caractere por caractere
         nome[52][31], //matriz que guarda os nomes de cada rotulo traduzido pelo dicionario
         predecessor; //rotulo que precede o rotulo principal
    int duracao, //variavel que guarda a duracao de cada atividade
        ordTop[52], //array que guarda os nohs ordenados topologicamente
        TMT[52], //variavel que guarda os tempos minimos de cada noh da ordenacao topologica
        caminhoCritico[52], //array que guarda os pais para determinar o caminho critico
        dur[52]; //guarda as duracoes dos nohs do caminho critico
    
    memset(visited, false, sizeof(visited)); //nenhum noh visitado ainda
    memset(ancestral, false, sizeof(ancestral)); //nenhum ancestral visitado ainda
    p = NULL; //inicializando a pilha global
    for (int i = 0; i < 53; i++)
        for (int j = 0; j < 53; j++)
            grafo[i][j] = inf; //nenhum noh esta conectado ainda
    for (int i = 0; i < 7; i++)
        fgets(lixo, 72, e); //7 primeiras linhas sao inuteis
        
    fprintf(s, "Acabouuu\n");
    fprintf(s, "CES-11 neh\n");
    fprintf(s, "Ainda tem MPG-04 pra segunda-feira\n");
    fprintf(s, "Deseje-me sorte :(\n\n");
    fprintf(s, "------------------------------------------------------------\n\n");
    
    do
    {
        fscanf(e, " %c ", &rotulo); //leitura do rotulo
        
        if (rotulo != '-')
        {
            for (int i = 0; i < 30; i++)
            {
                fscanf(e, "%c", &carac); //lendo 30 caracteres
                nome[dicionario(rotulo)][i] = carac; //e construindo a string
            }
            nome[dicionario(rotulo)][30] = '\0'; //finalizando a string
            
            fscanf(e, "%d ", &duracao); //leitura da duracao
            do
            {
                fscanf(e, "%c%c", &predecessor, &carac); //leitura dos predecessores
                if (predecessor == '.') //nao tem nenhum predecessor
                    grafo[inicio][dicionario(rotulo)] = duracao; //entao seu predecessor eh o inicio
                else
                    grafo[dicionario(predecessor)][dicionario(rotulo)] = duracao; //se tiver predecessor, cria aresta
            } while (carac != '\n');
        }
    } while (rotulo != '-');
    
    ciclico = false; //nao sera ciclo
    for (int i = inicio; i >= 0 && ciclico == false; i--) //se nao encontrar ciclo por dfs
        depthFirstSearch(i);
    
    if (ciclico == true) //se for ciclo, nao ha caminho critico
    {
        fprintf(s, "CICLO ENCONTRADO:\n\n");
        
        fprintf(s, "%c", retorno(pivot)); //printando o noh armanezado no pivot
        for (int aux = caminhoCiclo[pivot]; aux != pivot; aux = caminhoCiclo[aux])
            fprintf(s, " %c", retorno(aux)); //e printando o ciclo
        fprintf(s, "\n\n");
        
        fprintf(s, "------------------------------------------------------------\n\n");
        fprintf(s, "CAMINHO CRÍTICO:\n\n");
        fprintf(s, "Impossível buscar caminho crítico!\n");
    }
    else //se nao for ciclo
    {
        for (int i = 0; i < 53; i++) //nenhum noh visitado ainda
            visited[i] = false;
        ordenacaoTopologica(inicio); //realiza-se a ordenacao topologica
        
        fprintf(s, "UMA ORDENACAO TOPOLOGICA:\n\n");
        int tam = 0; //tam armazenara quantos nohs tem na ordenacao topologica
        while (ordemTopologica != NULL) //e transfere a ordem topologica da pilha pro array
        {
            fprintf(s, "%c%c", retorno(top(ordemTopologica)), ordemTopologica->next == NULL ? '\n' : ' ');
            ordTop[tam++] = top(ordemTopologica);
            ordemTopologica = pop(ordemTopologica);
        }
        fprintf(s, "\n------------------------------------------------------------\n\n");
        fprintf(s, "CAMINHO CRÍTICO:\n\n");
        fprintf(s, "TAREFA        DESCRICAO           DURACAO\n\n");
        
        for (int i = 0; i < tam; i++)
            caminhoCritico[i] = -1; //nenhum noh tem pai por hora
        for (int i = 0; i < tam; i++) //para o noh i, armaneza o seu antecessor que tem o maior TMT + dist de ant a i
        {
            int ans = -1; //ans armazenara o TMT de cada noh
            for (int j = i - 1; j >= 0; j--)
                if (grafo[ordTop[j]][ordTop[i]] < inf && grafo[ordTop[j]][ordTop[i]] + TMT[j] > ans)
                {
                    ans = grafo[ordTop[j]][ordTop[i]] + TMT[j]; //atualiza-se ans
                    dur[i] = grafo[ordTop[j]][ordTop[i]]; //dur[i] recebe a duracao correspondente ao noh
                    caminhoCritico[i] = j; //j eh pai de i
                }
            dur[i] = ans == -1 ? grafo[inicio][ordTop[i]] : dur[i]; //se ans for -1, nao ha pai e dur[i] eh de inicio a i
            TMT[i] = ans == -1 ? grafo[inicio][ordTop[i]] : ans; //se ans for -1, o pai eh inicio
        }
        int ans = -1; //ans armazenara o maior TMT
        for (int i = 0; i < tam; i++)
            if (TMT[i] > ans) //algoritmo para achar o maior
            {
                ans = TMT[i];
                pivot = i; //e pivot guarda a posicao correspondente ao maior, ultimo do caminho critico
            }
        for (int i = pivot; i != -1; i = caminhoCritico[i])
            p = push(p, i); //insere numa pilha
        while (p != NULL) //para entao inverter a ordem e printar do jeito requisitado
        {
            pivot = top(p);
            fprintf(s, "  %c   %s%3d\n", retorno(ordTop[pivot]), nome[ordTop[pivot]], dur[pivot]);
            p = pop(p);
        }
        fprintf(s, "                                   ----\n");
        fprintf(s, "TEMPO MINIMO PARA O PROJETO:         %d semanas\n", ans);
    }
    
    fclose(e);
    fclose(s);
    
    return 0;
}
