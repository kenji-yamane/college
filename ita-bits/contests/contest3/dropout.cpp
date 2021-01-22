#include <bits/stdc++.h>


using namespace std;

int main() {
	ios_base::sync_with_stdio(true);
	cin.tie(NULL);
	int N, x;
	string aux;

	while (true) {
		vector<string> names;
		queue<int> deck;

		cin >> N;
		if (!N) break;

		for (int i = 0; i < N; i++) {
			cin >> aux;
			names.push_back(aux);
		}
		for (int i = 0; i < 52; i++) {
			cin >> x;
			deck.push(x);
		}
		
		bool over = false;
		while (not over) {
			if (deck.size() < names.size()) {
				over = true;
			}
			else {
				vector<int> turn;
				for (int i = 0; i < (int)names.size(); i++) {
					turn.push_back(deck.front());
					deck.pop();
				}
				int min = 14;
				for (int i = 0; i < (int)turn.size(); i++) {
					if (min > turn[i]) min = turn[i];
				}
				int eliminated = 0;
				for (int i = 0; i < (int)turn.size(); i++) {
					if (min == turn[i]) eliminated++;
				}
				if (eliminated == (int)names.size()) {
					over = true;
				}
				else {
					for (int i = 0; i < (int)turn.size(); i++) {
						if (min == turn[i]) {
							turn.erase(turn.begin() + i);
							names.erase(names.begin() + i);
							i--;
						}
					}
				}
			}
		}
		for (int i = 0; i < (int)names.size(); i++) {
			cout << names[i] << " ";
		}
		cout << endl;
	}

	return 0;
}
