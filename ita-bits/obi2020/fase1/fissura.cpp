#include <bits/stdc++.h>


using namespace std;

int N;
char terrain[500][500], force;

void move(int i, int j) {
	if (terrain[i][j] > force || terrain[i][j] == '*') return;

	terrain[i][j] = '*';
	if (i + 1 < N) move(i + 1, j);
	if (i > 0) move(i - 1, j);
	if (j + 1 < N) move(i, j + 1);
	if (j > 0) move(i, j - 1);
}

int main() {
	int F;

	scanf("%d %d", &N, &F);
	force = '0' + F;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf(" %c", &terrain[i][j]);
		}
	}
	
	move(0, 0);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%c", terrain[i][j]);
		}
		printf("\n");
	}

	return 0;
}
