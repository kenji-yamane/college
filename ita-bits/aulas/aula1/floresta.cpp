#include <cstdio>


int rootSquare(int N)
{
	int ans = 1;
	
	while (ans*ans < N)
		ans++;
	
	return ans;
}

int main()
{
	//i*j + (i - 1)*(j - 1) = input
	//i*j + i*j - i - j + 1 = input
	//4*i*j - 2*i - 2*j + 1 = 2*input - 1
	//2*i*(2*j - 1) - (2*j - 1) = 2*input - 1
	//(2*i - 1)*(2*j - 1) = 2*input - 1
	
	int N, ans = 0, root;
	
	scanf("%d", &N);
	root = rootSquare(2*N - 1);
	for (int i = 3; i <= root; i += 2)
		if ((2*N - 1)%i == 0)
			ans++;
	printf("%d\n", ans);
	
	return 0;
}
