#include <bits/stdc++.h>


using namespace std;

//Força bruta
//testar as combinações de 3 a 3

int main()
{
	int A, B, C, D;

	scanf("%d %d %d %d", &A, &B, &C, &D);

	if (A < B + C and A > abs(B - C))
		printf("S\n");
	else if (A < B + D and A > abs(B - D))
		printf("S\n");
	else if (A < C + D and A > abs(C - D))
		printf("S\n");
	else if (B < C + D and B > abs(C - D))
		printf("S\n");
	else
		printf("N\n");

	return 0;
}
