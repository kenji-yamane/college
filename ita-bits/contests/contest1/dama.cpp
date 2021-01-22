#include <bits/stdc++.h>


using namespace std;

int main()
{
	pair<int, int> begin, end, diff;
	
	while (true)
	{
		scanf("%d %d %d %d", &begin.first, &begin.second, &end.first, &end.second);
		if (!begin.first and !begin.second and !end.first and !end.second) break;
		diff.first = abs(begin.first - end.first);
		diff.second = abs(begin.second - end.second);
		
		if (!diff.first && !diff.second)
			printf("0\n");
		else if (diff.first == diff.second || !diff.first || !diff.second)
			printf("1\n");
		else
			printf("2\n");
	}
	
	return 0;
}
