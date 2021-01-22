#include <bits/stdc++.h>


using namespace std;

bool sortProcessed(pair<int, int> &a, pair<int, int> &b)
{
	return (a.first < b.first);
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int N, time;
	pair<int, int> processed[100000];
	
	while (cin >> N)
	{
		for (int i = 0; i < N; i++)
			cin >> processed[i].first >> processed[i].second;
		sort(processed, processed + N, sortProcessed);
		
		time = 0;
		for (int i = 0; i < N; i++)
		{
			if (time < processed[i].first)
				time = processed[i].first;
			time += processed[i].second;
		}
		cout << time << endl;
	}
	
	return 0;
}
