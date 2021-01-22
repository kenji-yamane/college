#include <iostream>
#include <map>


using namespace std;

int main()
{
	int N, M, P, qtd;
	string aux;
	float price, ans;
	map<string, float> fruits;
	
	cin >> N;
	while (N--)
	{
		ans = 0;
		cin >> M;
		while (M--)
			cin >> aux >> price, fruits[aux] = price;
		cin >> P;
		while (P--)
			cin >> aux >> qtd, ans += fruits[aux]*qtd;
		printf("R$ %.2f\n", ans);
		fruits.clear();
	}
	
	return 0;
}
