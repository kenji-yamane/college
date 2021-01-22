#include <cstdio>
#include <cstdlib>
#include <utility>


using namespace std;

int MDC(int a, int b)
{
	if (b == 0)
		return a;
	
	return MDC(b, a%b); //algoritmo de euclides para achar o mdc
}

int main()
{
	int N, mdc;
	char o;
	pair<int, int> fr1, fr2, ans;
	
	scanf("%d", &N);
	while (N--)
	{
		scanf("%d / %d %c %d / %d", &fr1.first, &fr1.second, &o, &fr2.first, &fr2.second);
		ans.second = fr1.second*fr2.second;
		
		if (o == '+')
			ans.first = fr1.first*fr2.second + fr2.first*fr1.second;
		else if (o == '-')
			ans.first = fr1.first*fr2.second - fr2.first*fr1.second;
		else if (o == '*')
			ans.first = fr1.first*fr2.first;
		else
		{
			ans.first = fr1.first*fr2.second;
			ans.second = fr2.first*fr1.second;
		}
		
		mdc = MDC(abs(ans.first), abs(ans.second));
		printf("%d/%d = %d/%d\n", ans.first, ans.second, ans.first/mdc, ans.second/mdc);
	}
	
	return 0;
}
