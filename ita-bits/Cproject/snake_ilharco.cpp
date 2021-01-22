#include <stdio.h>

//using serve para importar arquivos, é como um include
#using <mscorlib.dll>


/*namespace são "recipientes" abstratos que servem para não criar ambiguidade quando temos diferentes identificadores
com o mesmo nome, ou seja servem para criar escopo de nome. Por exemplo, podem existir duas funções com o mesmo nome, mas em diferentes namespaces, então quando você for chamar uma delas, deve ser especificado de qual namespace se trata.

A sintaxe using namespace nome_do_namespace significa que queremos usar o que está nesse namespace.
*/
using namespace System;


/*------------------------------------------------------------------------------------------------------------------------------*/
//variáveis globais
/*essas variáveis são declaradas normalmente como geralmante fazemos dentro da main, a diferença é que assim
podemos usá-las em qualquer parte do código, dentro de funções por exemplo, sem precisar passá-las como parâmetros.
*/
ConsoleKeyInfo comando;	//serve para pegar as teclas apertadas pelo jogador
int x,y;	//variáveis que serão usadas para guardar a posição na tela

/*------------------------------------------------------------------------------------------------------------------------------*/


//funções
void anda(){
	//checa se alguma tecla foi pressionada
	if (Console::KeyAvailable){
			comando=Console::ReadKey(true);	//a variável comando recebe a tecla pressionada
	}

	//apaga o último caractere desenhado
	Console::SetCursorPosition(x,y);
	printf(" ");
	
	//checa se o botão pressionado foi uma das setas e faz a devida variação nas variéveis x e y.
	if (comando.Key==ConsoleKey::UpArrow){
		y--;
	}
	else if (comando.Key==ConsoleKey::DownArrow){
		y++;
	}
	else if (comando.Key==ConsoleKey::LeftArrow){
		x--;
	}
	else if (comando.Key==ConsoleKey::RightArrow){
		x++;
	}
}

//imprime na tela o caractere na posição desejada
void imprime(){
	//se saiu da tela volta para dentro
	if(x<0)	x=0;
	if(y<0)	y=0;
	
	//move o cursor pro local onde queremos imprimir
	Console::SetCursorPosition(x,y);

	//imprime
	printf("O");
}

/*------------------------------------------------------------------------------------------------------------------------------*/
int main(){
	x=y=0;
	
	//serve para que o cursor não fique piscando, descomente a linha para ver a diferença
	//Console::CursorVisible = false;

	
	//o sistema de coordenadas tem o eixo y orientado pra baixo :)
	//a origem fica no canto superior esquerdo da tela.
	/*Console::SetCursorPosition(10,10);
	printf("O");
	*/


	//desenhando na tela
	/*
	//desenha uma linha vertical
	for(int i=0; i<10; i++){
		Console::SetCursorPosition(25,i+4);
		printf("%c", '|');
	}
	//linha horizontal
	for(int i=0; i<10; i++){
		Console::SetCursorPosition(i+3,22);
		printf("_");
	}
	//retangulo
	for(int i=0; i<10; i++){
		Console::SetCursorPosition(i+2, 1);
		printf("_");
		Console::SetCursorPosition(i+2, 11);
		printf("_");
		Console::SetCursorPosition(1, i+2);
		printf("|");
		Console::SetCursorPosition(12, i+2);
		printf("|");
	}
	*/


	/*	while(true) funciona como qualquer outro while, checa se a condição que está entre parênteses é verdadeira
	se for, executa o bloco de código e repete-se o processo
	se não, termina o while. 
		O que tem de especial é que a condição que está entre parênteses (true) é sempre verdadeira, independente 
	de qualquer coisa, então o while vai continuar infinitamente a não ser que o código que está dentro
	do bloco do while tenha algum comando como o break(que vocês não viram), que o faça sair do while
	*/
	while(true){
		imprime();	//chama a função imprime() que foi definida anteriormente
		Threading::Thread::Sleep(100);	//chama a função sleep que produz uma pausa na execução do programa.
		anda();	//chama a função anda()
	}

	fflush(stdin);
	getchar();
	return 0;
}
