#include <iostream>
#include <map>


using namespace std;

int main()
{
	int N, M, errors, ans;
	string aux1, aux2;
	
	while (true)
	{
		cin >> N;
		if (N == 0) break;
		ans = 0;
		map<string, string> presence;
		while (N--)
			cin >> aux1 >> aux2, presence[aux1] = aux2;
		cin >> M;
		while (M--)
		{
			cin >> aux1 >> aux2;
			aux1 = presence[aux1];
			errors = 0;
			for (int i = 0; i < (int)aux1.size(); i++)
				if (aux1[i] != aux2[i])
					errors++;
			
			if (errors > 1) ans++;
		}
		cout << ans << endl;
	}
	
	return 0;
}
