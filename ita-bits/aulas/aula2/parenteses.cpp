#include <cstdio>
#include <cstring>
#include <stack>


using namespace std;

int main()
{
	int len, i;
	char str[1002];
	
	while (fgets(str, 1002, stdin) != NULL) //funcao de entrada q le uma linha inteira
	{
		bool correct = true;
		stack<char> par;
		len = strlen(str);
		for (i = 0; i < len && correct; i++)
			if (str[i] == '(')
				par.push(str[i]);
			else if (str[i] == ')' && par.empty())
				correct = false;
			else if (str[i] == ')' && par.top() == ')')
				correct = false;
			else if (str[i] == ')' && par.top() == '(')
				par.pop();
		if (!par.empty())
			correct = false;
		printf("%s\n", correct == true ? "correct" : "incorrect");
	}
	
	return 0;
}
