#include <bits/stdc++.h>


using namespace std;

int L, C, salon[1000][1000];
bool found = false;

void walk(int A, int B)
{
	salon[A][B] = 0;
	if (A < L - 1 && salon[A + 1][B] == 1)
		walk(A + 1, B);
	else if (A > 0 && salon[A - 1][B] == 1)
		walk(A - 1, B);
	else if (B < C - 1 && salon[A][B + 1] == 1)
		walk(A, B + 1);
	else if (B > 0 && salon[A][B - 1] == 1)
		walk(A, B - 1);
	
	if (found == false)
		printf("%d %d\n", A + 1, B + 1), found = true;
}

int main()
{
	int A, B;

	scanf("%d %d %d %d", &L, &C, &A, &B);
	for (int i = 0; i < L; i++)
		for (int j = 0; j < C; j++)
			scanf("%d", &salon[i][j]);
	walk(A - 1, B - 1);

	return 0;
}
