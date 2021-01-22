#include <bits/stdc++.h>
#define inf 999999999999


using namespace std;

//vai dividindo conforme o problema indicou q vai dar bom
//porém utilize de forma inteligente os dados

long long A, B, untreatedAvengers[100000], k;
pair<long long, int> avengers[100000];

long long binary_search(long long ini, long long fim, long long searched)
{
	if (ini > fim) return fim;
	int meio = (ini + fim)/2;

	if (searched < avengers[meio].first)
		return binary_search(ini, meio - 1, searched);
	else if (avengers[meio].first < searched)
		return binary_search(meio + 1, fim, searched);
	else
		return meio;
}

long long minimal(long long ini, long long fim)
{
	if (ini > fim) return inf;
	long long nAvengers = 0;
	long long findIni = binary_search(0, k, ini); //mesmo se ini n existir em avengers, retorna um valor prox
	long long findFim = binary_search(0, k, fim); //mesma coisa com o fim
	long long meio = (ini + fim)/2;

	for (long long i = findIni - 3; i < findFim + 4; i++) //o 3 e 4 carteado é pq eu n sei o quão prox rs
		if (i >= 0 && i < k && avengers[i].first <= fim && avengers[i].first >= ini)
			nAvengers += avengers[i].second;
	
	if (nAvengers == 0 && fim - ini + 1 > 1)
		return A;
	else if (ini == fim)
	{
		if (nAvengers == 0)
			return A;
		else
			return nAvengers*B;
	}
	else
		return min(B*nAvengers*(fim - ini + 1), minimal(ini, meio) + minimal(meio + 1, fim));
}

int main()
{
	long long n;
	int ctrl = 0;

	scanf("%lld %lld %lld %lld", &n, &k, &A, &B);
	for (int i = 0; i < k; i++)
		scanf("%lld", &untreatedAvengers[i]), untreatedAvengers[i]--;
	sort(untreatedAvengers, untreatedAvengers + k);
	avengers[ctrl] = make_pair(untreatedAvengers[0], 0);
	for (int i = 0; i < k; i++)
		if (untreatedAvengers[i] == avengers[ctrl].first)
			avengers[ctrl].second++;
		else
			avengers[++ctrl] = make_pair(untreatedAvengers[i], 1);
	k = ctrl + 1;
	
	printf("%lld\n", minimal(0, pow(2, n) - 1));

	return 0;
}
