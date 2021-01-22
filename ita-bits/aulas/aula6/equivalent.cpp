#include <bits/stdc++.h>


using namespace std;

//usar 4 recursões seria O(N^2)
//para evitar, reordena-se lexicograficamente

bool equivalent(string &a, string &b)
{
	if (a.size()%2 != 0 || b.size()%2 != 0)
	{
		if (a == b)
			return true;
		else
			return false;
	}
	
	string a1, a2, b1, b2;

	for (int i = 0; i < (int)a.size()/2; i++)
		a1.push_back(a[i]), b1.push_back(b[i]);
	for (int i = (int)a.size()/2; i < (int)a.size(); i++)
		a2.push_back(a[i]), b2.push_back(b[i]);

	bool first = equivalent(a1, b2);
	bool second = equivalent(a2, b1);

	a = a1 < a2 ? (a1 + a2) : (a2 + a1);
	b = b1 < b2 ? (b1 + b2) : (b2 + b1);

	if ((first && second) || a == b)
		return true;
	else
		return false;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	string a, b;

	cin >> a >> b;
	if (equivalent(a, b))
		cout << "YES" << endl;
	else
		cout << "NO" << endl;

	return 0;
}
