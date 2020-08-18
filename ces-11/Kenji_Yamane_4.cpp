/*  Kenji Yamane                    */
/*  Turma 3                         */
/*                                  */
/*  Exercicio 4: Banco              */

/*  CES-11: Algoritmos e Estruturas de Dados
    Prof. Armando
    Setembro de 2019      */
    
/*  Programa compilado com Code::Blocks 17.12*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//--------------------------------------------------
//    elemento do vetor
//--------------------------------------------------

struct conta
{
    char nome[22]; //nome com no maximo 20 caracteres + \n + \0
    float saldo; //valor na conta
};

typedef struct conta conta;

//--------------------------------------------------
//    estrutura gerenciadora
//--------------------------------------------------

struct lista
{
    int ini; //numero para o inicio
    int fim; //numero para o fim
    int quant; //quantidade de contas criadas
    int tot; //numero maximo de contas que podem existir simultaneamente
    conta *vetor; //array que guarda a sequencia de informacoes
};

typedef struct lista lista;

//--------------------------------------------------
//    LISTAVAZIA
//--------------------------------------------------

//indica se a lista esta vazia
bool ListaVazia(lista *l)
{
    //se esta vazia, true, senao, false
    return l->quant == 0 ? true : false;
}

//--------------------------------------------------
//    LISTA CHEIA
//--------------------------------------------------

//indica se a lista esta cheia
bool ListaCheia(lista *l)
{
    //se esta cheia, true, senao, false
    return l->quant == l->tot ? true : false;
}

//--------------------------------------------------
//    FINALIZAR
//--------------------------------------------------

//libera a lista na heap
void Finalizar(lista *l)
{
    //o ponteiro para vetor
    free(l->vetor);
    //o ponteiro para o gerenciador
    free(l);
}

//--------------------------------------------------
//    ATUALIZARSALDO
//--------------------------------------------------

//modifica o saldo de uma pessoa em virtude de extrato
//ou saque
void AtualizarSaldo(lista *l, int posic, float delta)
{
    l->vetor[posic].saldo += delta;
}

//--------------------------------------------------
//    CONSULTARSALDO
//--------------------------------------------------

//dada uma posicao posic, retorna o saldo da pessoa
//correspondente e deixa seu nome no array nome
float ConsultarSaldo(lista *l, int posic, char nome[])
{
    strcpy(nome, l->vetor[posic].nome);
    return l->vetor[posic].saldo;
}

//--------------------------------------------------
//    DISTANCIA_CIRCULAR
//--------------------------------------------------

//calcula a distancia no array circular
//o ant deve ser anterior ao prox(no sentido da lista)
int distancia_circular(int ant, int prox, int tot)
{
    if (ant <= prox) //a diferenca eh positiva e corresponde a distancia
        return prox - ant;
    else //a diferenca eh negativa e assim prox - ant eh o complemento da distancia
        return prox - ant + tot;
}

//--------------------------------------------------
//    INICIALIZAR
//--------------------------------------------------

//aloca o espaco necessario e seta os parametros
void Inicializar(lista *l)
{
    l->ini = 0;
    l->fim = l->tot - 1;
    l->quant = 0;
    l->vetor = (conta*)malloc(l->tot*sizeof(conta));
}

//--------------------------------------------------
//    POSICAOVALIDA
//--------------------------------------------------

//Verifica se posic eh uma posicao sendo utilizada pela lista
bool PosicaoValida(lista *l, int posic)
{
    bool valid = false;
    
    //caso em que a lista nao vai ao fim e volta, e assim posic tem de estar entre ini e fim
    if (!ListaVazia(l) && l->ini <= l->fim && posic >= l->ini && posic <= l->fim && posic >= 0 && posic < l->tot)
        valid = true;
    //a lista vai ao fim e volta, assim posic tem de estar no complemento de entre ini e fim
    if (!ListaVazia(l) && l->ini > l->fim && (posic >= l->ini || posic <= l->fim) && posic >= 0 && posic < l->tot)
        valid = true;
    
    return valid;
}

//--------------------------------------------------
//    BUSCARPOSICAO
//--------------------------------------------------

//Retorna a posicao correspondente a um dado nome
int BuscarPosicao(lista *l, const char nome[])
{
    //qualquer nome que seja nao existira na lista vazia
    if (ListaVazia(l))
        return -1;
    
    //posic tera o valor do meio da lista
    //o primeiro caso do operador ternario eh o da lista que nao vai e volta
    //assim posic eh a media aritmetica
    //o segundo caso a lista vai e volta, assim "desloca-se" fim para um l->tot a frente e faz a media
    int posic = ((l->ini + (l->ini <= l->fim ? l->fim : (l->fim + l->tot)))/2)%l->tot;
    
    //achou o nome ja no meio
    if (strcmp(l->vetor[posic].nome, nome) == 0)
        return posic;
    //o nome esta a esquerda
    else if (strcmp(l->vetor[posic].nome, nome) < 0)
        while (posic != (l->fim + 1)%l->tot && strcmp(l->vetor[posic].nome, nome) < 0) //ate achar ou chegar ao fim
            posic = (posic + 1)%l->tot; //iteracao circular
    //o nome esta a direita
    else if (strcmp(l->vetor[posic].nome, nome) > 0)
        while (posic != (l->ini - 1 + l->tot)%l->tot && strcmp(l->vetor[posic].nome, nome) > 0) //ate achar ou chegar ao ini
            posic = (posic - 1 + l->tot)%l->tot; //iteracao circular
    
    //se foi achado, ele corresponde a posicao posic
    if (PosicaoValida(l, posic) && strcmp(l->vetor[posic].nome, nome) == 0)
        return posic;
    
    //se nao achou, retorna -1, como especificado no enunciado
    return -1;
}

//--------------------------------------------------
//    REMOVER
//--------------------------------------------------

//remove um elemento da lista
void Remover(lista *l, int posic)
{   
    //o mais proximo e portanto que requer menor shift eh o ini
    if (distancia_circular(l->ini, posic, l->tot) < distancia_circular(posic, l->fim, l->tot))
    {
        //execucao do algoritmo de shift para a esquerda(porem modulo l->tot)
        for (int i = posic; i != l->ini; i = (i - 1 + l->tot)%l->tot)
        {
            //o atual recebe os dados de lista do anterior
            strcpy(l->vetor[i].nome, l->vetor[(i - 1 + l->tot)%l->tot].nome);
            l->vetor[i].saldo = l->vetor[(i - 1 + l->tot)%l->tot].saldo;
        }
        l->ini = (l->ini + 1)%l->tot; //atualizando o ini
    }
    //o mais proximo eh o fim, ou no caso em que a distancia eh igual
    else
    {
        //execucao do algoritmo de shift para a direita (porem modulo l->tot)
        for (int i = posic; i != l->fim; i = (i + 1)%l->tot)
        {
            //o atual recebe os dados de lista do posterior
            strcpy(l->vetor[i].nome, l->vetor[(i + 1)%l->tot].nome);
            l->vetor[i].saldo = l->vetor[(i + 1)%l->tot].saldo;
        }
        l->fim = (l->fim - 1 + l->tot)%l->tot; //atualizando o fim
    }
    l->quant--; //atualizando quant
}

//--------------------------------------------------
//    INSERIR
//--------------------------------------------------

//insere um elemento na lista, com saldo 0
void Inserir(lista *l, const char nome[])
{
    //se a lista estiver vazia, deve-se setar os parametros da seguinte forma
    if (ListaVazia(l))
    {
        l->ini = l->fim = 0;
        strcpy(l->vetor[0].nome, nome);
        l->vetor[0].saldo = 0;
        l->quant++;
        return;
    }
    //se nao estiver vazia, adquire-se novamente o meio
    int i, meio = ((l->ini + (l->ini <= l->fim ? l->fim : (l->fim + l->tot)))/2)%l->tot;
    
    //se o nome estiver a esquerda do meio, o shift da esquerda eh o mais simples
    if (strcmp(nome, l->vetor[meio].nome) < 0)
    {
        //execucao do shift de insercao, liberando o espaco em i - 1 no final
        for (i = l->ini; strcmp(l->vetor[i].nome, nome) < 0; i = (i + 1)%l->tot)
        {
            //o atual eh transferido para tras
            strcpy(l->vetor[(i - 1 + l->tot)%l->tot].nome, l->vetor[i].nome);
            l->vetor[(i - 1 + l->tot)%l->tot].saldo = l->vetor[i].saldo;
        }
        
        //insere os dados requeridos na posicao liberada i - 1
        strcpy(l->vetor[(i - 1 + l->tot)%l->tot].nome, nome);
        l->vetor[(i - 1 + l->tot)%l->tot].saldo = 0;
        l->ini = (l->ini - 1 + l->tot)%l->tot; //atualiza-se ini
        l->quant++; //atualiza-se quant
    }
    //se estiver a direita ou igual, o shift da direita eh o priorizado
    else
    {
        //execucao do shift de insercao, liberando o espaco i + 1 no final
        for (i = l->fim; strcmp(nome, l->vetor[i].nome) < 0; i = (i - 1 + l->tot)%l->tot)
        {
            //o atual eh transferido para frente
            strcpy(l->vetor[(i + 1)%l->tot].nome, l->vetor[i].nome);
            l->vetor[(i + 1)%l->tot].saldo = l->vetor[i].saldo;
        }
        
        //insere os dados requeridos na posicao liberada i + 1
        strcpy(l->vetor[(i + 1)%l->tot].nome, nome);
        l->vetor[(i + 1)%l->tot].saldo = 0;
        l->fim = (l->fim + 1)%l->tot; //atualiza-se fim
        l->quant++; //atualiza-se quant
    }
}

//--------------------------------------------------
//    MAIN
//--------------------------------------------------

int main()
{
    FILE *e = fopen("C:\\Lab4\\entrada4.txt", "r");
    FILE *s = fopen("C:\\Lab4\\kenjiyamane4.txt", "w");
    lista *l = (lista*)malloc(sizeof(lista));
    int i, posic;
    float dinheiro;
    char linha[52], name[22], command[12];
    
    //cinco primeiras linhas nao serao processadas
    for (i = 0; i < 5; i++)
        fgets(linha, 52, e);
    fscanf(e, "%d\n\n", &l->tot);
    Inicializar(l);
    
    //Primeiras quatro frases
    fprintf(s, "JoseLloyds Bank\n");
    fprintf(s, "La apresentacion de la quimica\n");
    fprintf(s, "Hola\n\n");
    fprintf(s, "RESULTADOS DAS CONSULTAS\n\n");
    do
    {
        fscanf(e, " %s ", command);
        
        if (strcmp(command, "ABRE_CONTA") == 0)
        {
            fgets(name, 22, e);
            
            if (ListaCheia(l)) //erro de lista lotada
                fprintf(s, "ERRO: Lista lotada. Impossível abrir conta\n");
            else if (BuscarPosicao(l, name) != -1) //o nome ja esta na lista
                fprintf(s, "ERRO: Ja existe conta com nome %s", name);
            else
                Inserir(l, name); //sem erros, insere-se
        }
        else if (strcmp(command, "DEPOSITO") == 0)
        {
            fscanf(e, "%f ", &dinheiro);
            fgets(name, 22, e);
            
            posic = BuscarPosicao(l, name);
            if (posic == -1) //verificando se existe a conta
                fprintf(s, "ERRO: Nao encontrado cliente com nome %s", name);
            else
                AtualizarSaldo(l, posic, dinheiro); //se sim, realiza-se o deposito
        }
        else if(strcmp(command, "SAQUE") == 0)
        {
            fscanf(e, "%f ", &dinheiro);
            fgets(name, 22, e);
            
            posic = BuscarPosicao(l, name);
            if (posic == -1) //verificando se existe a conta
                fprintf(s, "ERRO: Nao encontrado cliente com nome %s", name);
            else
                AtualizarSaldo(l, posic, -1*dinheiro); //se sim, realiza-se o saque
        }
        else if (strcmp(command, "EXTRATO") == 0)
        {
            fgets(name, 22, e);
            
            posic = BuscarPosicao(l, name);
            if (posic == -1) //verificando se existe a conta
                fprintf(s, "ERRO: Nao encontrado cliente com nome %s", name);
            else
                fprintf(s, "Saldo%9.2f  %s", ConsultarSaldo(l, posic, name), name); //se sim, expoe-se os dados
        }
        else if (strcmp(command, "FECHA_CONTA") == 0)
        {
            fgets(name, 22, e);
            
            posic = BuscarPosicao(l, name);
            if (posic == -1) //verificando se existe a conta
                fprintf(s, "ERRO: Nao encontrado cliente com nome %s", name);
            else
                Remover(l, posic); //se sim, ela eh removida
        }
    } while (strcmp(command, "FIM") != 0);
    
    //nas cinco proximas linhas, expoe-se as informacoes do gerenciador
    fprintf(s, "\nRELATORIO FINAL\n\n");
    fprintf(s, "Tamanho maximo da lista:%6d\n", l->tot);
    fprintf(s, "Total de correntistas:%8d\n", l->quant);
    fprintf(s, "Posicoes ocupadas: inicio:%4d\n", l->ini);
    fprintf(s, "                      fim:%4d\n\n", l->fim);
    
    //nas proximas linhas, mostra-se toda a lista
    fprintf(s, "CORRENTISTAS ATUAIS\n\n");
    i = l->ini;
    do
    {
        fprintf(s, "%8.2f  %s", ConsultarSaldo(l, i, name), name);
        i = (i + 1)%l->tot; //iteracoes circulares
    } while (i != (l->fim + 1)%l->tot);
    
    fclose(s);
    fclose(e);
    Finalizar(l);
    
    return 0;
}
