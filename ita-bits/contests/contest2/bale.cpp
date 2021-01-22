#include <bits/stdc++.h>


using namespace std;

//Dividir para conquistar
//a solução é o número de inversões necessárias para se ordenar o array
//pode-se aproveitar da estrutura otimizada do merge sort

int ans;

void mergeSort(vector<pair<int, int> > &v)
{
	if (v.size() == 1) return;
	vector<pair<int, int> > half1, half2;
	for (int i = 0; i < (int)v.size()/2; i++)
		half1.push_back(v[i]);
	for (int i = v.size()/2; i < (int)v.size(); i++)
		half2.push_back(v[i]);
	
	mergeSort(half1);
	mergeSort(half2);
	v.clear();
	int i = 0, j = 0;
	while (i < (int)half1.size() || j < (int)half2.size())
	{
		if (i == (int)half1.size())
			v.push_back(half2[j++]);
		else if (j == (int)half2.size())
			v.push_back(half1[i++]);
		else if (half1[i].second < half2[j].second)
			v.push_back(half1[i++]);
		else
			v.push_back(half2[j++]), ans += half1.size() - i; //inverteu essa qtd de vezes
	}
}

int main()
{
	int N, aux;
	vector<pair<int, int> > v;

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d", &aux), v.push_back(make_pair(i, aux));
	
	mergeSort(v);
	printf("%d\n", ans);

	return 0;
}
