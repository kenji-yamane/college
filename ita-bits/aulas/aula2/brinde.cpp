#include <iostream>
#include <stack>
#include <string> //estrutura de dados para string


using namespace std;

int main()
{
	int N, i, ans = 0;
	char letter;
	stack<string> s; //pilha de strings
	string aux = "FACE"; //strings em c++ são que nem qualquer variável
	
	s.push(aux);
	cin >> N;
	for (i = 0; i < N; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			scanf(" %c", &letter);
			aux[j] = letter;
		}
		
		bool contrary = true;
		for (int j = 0; j < 4; j++)
			if (aux[j] != s.top()[3 - j]) //lembre-se que s.top() eh uma string
				contrary = false;
		
		if (contrary == true)
			s.pop(), ans++; //se separar comandos por virgulas n precisa por chaves
		else
			s.push(aux);
		if (s.empty())
			aux = "FACE", s.push(aux);
	}
	
	printf("%d\n", ans);
	
	return 0;
}
