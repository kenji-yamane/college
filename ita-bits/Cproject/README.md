# Projeto C ITAbits 2020

O projeto para este ano proposto pela itabits para os bixos ao final do Treinamento de C é o de recriar o jogo SNAKE no console utilizando C. Será preciso alguns recursos, para facilitar a vida, advindos de C++, conforme descrito melhor abaixo.

## Considerações iniciais

Existem várias formas de codar o jogo Snake, inclusive formas que usam quase nenhum ou nenhum recurso de C++. Fica a cargo do bixo pesquisar a respeito e utilizar os recursos que julgar conveniente. O objetivo primordial deste desafio é permitir ao bixo ter contato direto com jogos e aprender formas legais de manipular o console, desenhar nele e interagir com ele, fugindo (ou tentando fugir) dos problemas vistos até então.

## Pré-requisitos

### Bibliotecas

Como dito acima, há algumas maneiras de se implementar tal desafio. Contudo, há algumas bibliotecas que costumas ajudar. Considere pesquisar sobre o que a inclusão de cada uma destas linhas pode fazer pelo seu código. No pior dos casos, você vai descobrir novas bibliotecas e recursos pra fazer coisas legais que venham à mente ;)

    #include<windows.h>
    #include<stdio.h>
    #include<conio.h>
    #include<iostream>
    #include <stdlib.h>
    #include <time.h>
    #include "stdafx.h"
    #using <mscorlib.dll>

### Funções / comandos bizus

Considere usar algo assim para mover o cursor pelo console dados as coordenadas x e y (atentar para a orientação dos eixos e origem na parte superior esquerda da tela).

    void mgotoxy(int x, int y)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y});
    }

De forma que desenhar o tabuleiro, por exemplo, ficaria algo assim:

    // Printa as bordas da tela, setando a posição do cursor e printando na posição setada
    for(int i = BORDA_INF; i <= BORDA_SUP; i++)
    {
        Console::SetCursorPosition(BORDA_INF, i); printf("*");
        Console::SetCursorPosition(BORDA_SUP, i); printf("*");
        Console::SetCursorPosition(i, BORDA_INF); printf("*");
        Console::SetCursorPosition(i, BORDA_SUP); printf("*");
    }
    
Para guardar um input do usuário, considere usar algo como
    
    // Declaração de variável do tipo ConsoleKey (um tipo como int, float, etc, porém, guarda uma tecla)
    ConsoleKey comando; // guardará o q o usuario digitou
    
    // Verifica se o usuário apertou uma tecla
    if (Console::KeyAvailable)
    {
        comando = Console::ReadKey(true).Key;
    }
    
Para movimentar o cursor a partir de comandos dados via teclado, considere usar algo como

    // Atualiza a direção em que a snake deve seguir
    if (comando == ConsoleKey::D || comando == ConsoleKey::RightArrow) {
        velx = VELOCIDADE; vely = 0;
    }
    
Para setar posições aleatórias, considere usar algo como

    comida_x = rand()%(BORDA_SUP-1)+1; // seta aleatoriamente uma comida, com x e y entre 1 e BORDA_SUP-1
    
Para definir pausas, considere usar algo como

    Sleep(velo);

ou

    using namespace System::Threading;
    //define quanto tempo o  sera o delay de cada "frame" do jogo
    Thread::Sleep(1000/DIFICULDADE);

Há outras formas de fazer tudo isso, sinta-se à vontade de pesquisar para conseguir fazer funcionar cada uma das partes do seu código :)

## Considerações finais

A estrutura de um jogo sempre é algo do tipo

- 1o: estado inicial --> Declarar e inicializar as variáveis de interesse que serão usadas ao longo do jogo, desenhar o estado inicial do jogo, que no caso é o "tabuleiro" (campo com bordas), a posição da comida e a posição inicial da cobra.

- 2o: gameloop --> É quando o jogo está de fato rodando. Um jogo rodando essencialmente nada mais é que um loop


      while (true) {
        // jogo
      }


Onde as coisas acontecem indefinidamente e, de preferência, paralelamente.

- 3o: fim de jogo --> Delimite uma condição de parada para o jogo, que pode ser quando o jogador quiser (apertar algo para acabar o jogo) ou morrer (gameover), onde se é um boa prática dar feedback sobre scores ou outras métricas que tenham sido desenvolvidas/conquistadas ao longo do jogo.

Não se esqueça, por fim, que o objetivo sempre é se divertir e aprender coisas novas. Caso seja preciso ver o gabarito, não tem problema, contanto que o objetivo de cada um conseguir reproduzir por si a solução e ter um mínimo entendimento do que está acontecendo. Caso queira ver uma referência que use C mais diretamente, recomendamos [esta](https://github.com/jeffersonRibeiro/snake-c/blob/master/snake.c) (apesar de que com C o código fica mais longo e portanto menos simples). Qualquer coisa, procure seus veteranos, teremos o prazer em ajudar (#vetmae) :)


## Gabarito

Exemplos de código podem ser facilmente encontrados na internet. Os nossos possíveis "gabaritos" de códigos deixados por seus veteranos 
podem ser encontrados neste repositório: [gabarito-1](https://github.com/ITAbits/projeto-treinamento-c/blob/master/2020/snake_knupp.cpp)
e [gabarito-2](https://github.com/ITAbits/projeto-treinamento-c/blob/master/2020/snake_ilharco.cpp).

    
    
