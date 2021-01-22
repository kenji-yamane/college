#include <bits/stdc++.h>

using namespace std;

int k, a, b, ancestors[90000];
bool memo[300][300];
string str;

void divide(int posic, int divisions) {
	if (memo[posic][divisions] == true) return;
	memo[posic][divisions] = true;
	for (int i = a; i <= b && posic + i <= (int)str.size() && divisions < k; i++) {
		ancestors[(posic + i)*300 + divisions + 1] = posic*300 + divisions;
		divide(posic + i, divisions + 1);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	stack<int> divisions;

	cin >> k >> a >> b;
	cin >> str;

	divide(0, 0);
	if (memo[str.size()][k]) {
		int ancestor = str.size()*300 + k;
		while (ancestor != 0) {
			divisions.push((ancestor - ancestor%300)/300);
			ancestor = ancestors[ancestor];
		}
		for (int i = 0; i < (int)str.size(); i++) {
			cout << str[i];
			if (i == divisions.top() - 1) {
				cout << endl;
				divisions.pop();
			}
		}
	}
	else {
		cout << "No solution" << endl;
	}

	return 0;
}
