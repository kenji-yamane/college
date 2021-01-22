#include <iostream>
#include <set>


using namespace std;

int main()
{
	string aux;
	set<string> jewels;
	
	while (cin >> aux)
		jewels.insert(aux);
	
	cout << jewels.size() << endl;
	
	return 0;
}
