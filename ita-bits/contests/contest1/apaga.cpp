#include <bits/stdc++.h>


using namespace std;

int main()
{
	int N, D, i;
	char aux;
	deque<char> num, treated;
	
	while (true)
	{
		scanf("%d %d", &N, &D);
		if (!N && !D) break;
		
		for (i = 0; i < N; i++)
			scanf(" %c", &aux), num.push_back(aux);
		for (i = 0; i < D && num.size() > 1; i++)
		{
			if (!treated.empty() && treated.back() < num.front())
				treated.pop_back();
			else
			{
		    	if (num[0] < num[1])
		    	    num.pop_front();
	    	    else
	    	        treated.push_back(num.front()), num.pop_front(), i--;
			}
		}
		while (!treated.empty() && !num.empty() && treated.back() < num.front() && i < D)
			treated.pop_back(), i++;
		while (!num.empty())
			treated.push_back(num.front()), num.pop_front();
		while (i++ < D)
			treated.pop_back();
		while (!treated.empty())
			printf("%c", treated.front()), treated.pop_front();
		printf("\n");
	}
	
	return 0;
}
