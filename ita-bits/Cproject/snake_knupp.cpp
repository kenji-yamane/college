// SNAKE_KNUPP.cpp : main project file.

#include <stdio.h>
#using <mscorlib.dll>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

using namespace System::Threading;
using namespace System;

//variaveis globais do jogo
const int BORDA_INF = 0;
const int BORDA_SUP = 30;
const int TAMANHO_MAX = 100;
const int VELOCIDADE = 1;
const int Xinicial = 15;
const int Yinicial = 15;
const int DIFICULDADE = 2;

int main()
{
    /*-------------INICIALIZAÇÃO DO JOGO--------------------*/

    //gera um numero pseudo-aleatorio(gerado a partir de uma relaçao deterministica,
    //com semente a hora do relogio em tempo de execução
    srand(time(NULL));

    //Printa as bordas da tela, setando a posição do cursor
    for(int i = BORDA_INF; i <= BORDA_SUP; i++)
    {
        Console::SetCursorPosition(BORDA_INF, i); printf("*");
        Console::SetCursorPosition(BORDA_SUP, i); printf("*");
        Console::SetCursorPosition(i, BORDA_INF); printf("*");
        Console::SetCursorPosition(i, BORDA_SUP); printf("*");
    }

    //variaveis que guardam informaçoes sobre a snake
    int cobrax[TAMANHO_MAX], cobray[TAMANHO_MAX];
    int velx, vely;
    int tamanho;
    int comida_x, comida_y;
    ConsoleKey comando;//guardara o q o usuario digitou

    //seta os valores iniciais para o começo do jogo
    cobrax[0] = Xinicial; cobray[0] = Yinicial;//setando a cabeça da cobra numa posição inicial definida
    for(int i = 1; i < TAMANHO_MAX; i++){//guarda o "resto da snake" fora do campo
        cobrax[i] = BORDA_SUP+10; cobray[i] = BORDA_SUP+10;}
    velx = VELOCIDADE;
    vely = 0;
    tamanho = 10;
    comida_x = rand()%(BORDA_SUP-1)+1;//seta aleatoriamente uma comida, com x e y entre 1 e BORDA_SUP-1
    comida_y = rand()%(BORDA_SUP-1)+1;
    Console::SetCursorPosition(comida_x, comida_y);
    printf("+");//e printa a comida

    /*~~~~~~~~~~~~LOOP PRINCIPAL~~~~~~~~~~~~~~*/
    do
    {
        //Verifica se o usuario apertou uma tecla
        if(Console::KeyAvailable) comando = Console::ReadKey(true).Key;

        //atualiza a direção em q o snake deve seguir
        if(comando == ConsoleKey::D || comando == ConsoleKey::RightArrow){
            velx = VELOCIDADE; vely = 0;}
        else if(comando == ConsoleKey::A || comando == ConsoleKey::LeftArrow){
            velx = -VELOCIDADE; vely = 0;}
        else if(comando == ConsoleKey::W || comando == ConsoleKey::UpArrow){
            velx = 0;vely = -VELOCIDADE;}
        if(comando == ConsoleKey::S || comando == ConsoleKey::DownArrow){
            velx = 0;vely = VELOCIDADE;}

        //atualiza a posicao da snake
        cobrax[0] += velx; cobray[0] += vely;

        //se a snake passar da borda, joga ela pro inicio da outra borda
        if(cobrax[0] >= BORDA_SUP) cobrax[0] = BORDA_INF+1;
        if(cobray[0] >= BORDA_SUP) cobray[0] = BORDA_INF+1;
        if(cobrax[0] <= BORDA_INF) cobrax[0] = BORDA_SUP-1;
        if(cobray[0] <= BORDA_INF) cobray[0] = BORDA_SUP-1;

        //atualiza o vetor que guarda a snake
        for(int i = tamanho-1; i > 0; i--){
            cobrax[i] = cobrax[i-1]; cobray[i] = cobray[i-1];}

        //literalmente printa a snake(a cabeça dela)
        Console::SetCursorPosition(cobrax[0], cobray[0]);
        printf("%c", 1);//printf da carinha [ =) ]

        //define quanto tempo o  sera o delay de cada "frame" do jogo
        Thread::Sleep(1000/DIFICULDADE);

        //apaga por onde a snake estava andando
        Console::SetCursorPosition(cobrax[tamanho-1], cobray[tamanho-1]);
        printf(" ");
    }while(comando != ConsoleKey::Escape);

    /*--------MESAGEM DE FIM DO PROGRAMA----------*/
    Console::SetCursorPosition(0, BORDA_SUP+2);
    printf("IT'S OVER...");
	fflush(stdin);
	getchar();
    return 0;
}
