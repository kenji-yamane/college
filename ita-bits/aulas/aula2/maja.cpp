#include <cstdio>
#include <utility>


using namespace std;

int main()
{
	int N, i, j, step = 1;
	pair<int, int> majaCoordinate[100000]; //vetor de pairs
	pair<int, int> ctrl = {0, 0}; //inicializacao possivel para um pair
	majaCoordinate[0] = ctrl;
	
	i = 1;
	while (i < 100000)
	{
		for (j = 0; j < step && i < 100000; j++) //baixo
			ctrl.second++, majaCoordinate[i++] = ctrl;
		for (j = 0; j < step - 1 && i < 100000; j++) //baixo esquerda
			ctrl.first--, ctrl.second++, majaCoordinate[i++] = ctrl;
		for (j = 0; j < step && i < 100000; j++) //esquerda
			ctrl.first--, majaCoordinate[i++] = ctrl;
		for (j = 0; j < step && i < 100000; j++) //cima
			ctrl.second--, majaCoordinate[i++] = ctrl;
		for (j = 0; j < step && i < 100000; j++) //cima direita
			ctrl.first++, ctrl.second--, majaCoordinate[i++] = ctrl;
		for (j = 0; j < step && i < 100000; j++) //direita
			ctrl.first++, majaCoordinate[i++] = ctrl;
		step++;
	}
	
	while (scanf("%d", &N) != EOF)
		printf("%d %d\n", majaCoordinate[N - 1].first, majaCoordinate[N - 1].second);
	
	return 0;
}
