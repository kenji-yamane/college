#include <bits/stdc++.h>


using namespace std;

int main()
{
	int Q, iterators[200], serial = 0, ini, iAux;
	deque<int> letters[200]; //trate as letras separadamente
	char aux, str[101];
	bool matched;
	
	do
	{
		scanf("%c", &aux);
		if (aux != '\n')
			letters[(int)aux].push_back(serial++);
	} while (aux != '\n');

	scanf("%d", &Q);
	while (Q--)
	{
		matched = true;
		ini = -1;
		serial = 0;
		memset(iterators, 0, sizeof(iterators));
		scanf(" %s", str);

		int len = strlen(str);
		for (int i = 0; i < len && matched; i++)
		{
			iAux = (int)str[i];
			while (iterators[iAux] < (int)letters[iAux].size() && letters[iAux][iterators[iAux]] < serial)
				iterators[iAux]++;
			if (iterators[iAux] == (int)letters[iAux].size())
				matched = false;
			serial = letters[iAux][iterators[iAux]++];
			if (ini == -1)
				ini = serial;
		}

		if (matched)
			printf("Matched %d %d\n", ini, serial);
		else
			printf("Not matched\n");
	}

	return 0;
}
