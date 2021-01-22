#include <bits/stdc++.h>


using namespace std;

struct shop {
	int bread;
	char fill;
	int cost;
};

shop shops[1000];
int N, mp[200], memo[1000][1001][2][2][2];

int buy(int posic, int money, int fillings[]) {
	if (posic == N) return 0;
	if (memo[posic][money][fillings[0]][fillings[1]][fillings[2]] != -1) {
		return memo[posic][money][fillings[0]][fillings[1]][fillings[2]];
	}
	int picked = fillings[0] + fillings[1] + fillings[2];
	int ans = 0;

	if (money >= shops[posic].cost && (picked < 2 || fillings[mp[(int)shops[posic].fill]] == 1)) {
		int aux = fillings[mp[(int)shops[posic].fill]];
		fillings[mp[(int)shops[posic].fill]] = 1;
		ans = max(ans, shops[posic].bread + buy(posic + 1, money - shops[posic].cost, fillings));
		fillings[mp[(int)shops[posic].fill]] = aux;
	}
	ans = max(ans, buy(posic + 1, money, fillings));

	return memo[posic][money][fillings[0]][fillings[1]][fillings[2]] = ans;
}

int main() {
	int R, fillings[3] = {0};
	vector<int> types;
	memset(memo, -1, sizeof(memo));
	mp['B'] = 0;
	mp['C'] = 1;
	mp['G'] = 2;

	scanf("%d %d", &N, &R);
	for (int i = 0; i < N; i++) {
		scanf("%d %c %d", &shops[i].bread, &shops[i].fill, &shops[i].cost);
	}
	printf("%d\n", buy(0, R, fillings));

	return 0;
}
