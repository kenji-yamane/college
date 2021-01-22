#include <bits/stdc++.h>


using namespace std;

int letters;
set<string> ans;

void generate(string aux, string building)
{
	char keep;
	if (letters == (int)aux.size())
	{
		ans.insert(building);
		return;
	}
	for (int i = 0; i < (int)aux.size(); i++)
		if (aux[i] != '-')
		{
			building.push_back(aux[i]);
			keep = aux[i];
			aux[i] = '-';
			letters++;
			generate(aux, building);
			building.pop_back();
			letters--;
			aux[i] = keep;
		}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int n;
	string str, building;

	cin >> n;
	while (n--)
	{
		cin >> str;
		
		sort(str.begin(), str.end());
		generate(str, building);
		for (auto c : ans)
			cout << c << endl;
		cout << endl;
		ans.clear();
	}

	return 0;
}
