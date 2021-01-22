#include <bits/stdc++.h>


using namespace std;

struct tree {
	char info;
	tree *left;
	tree *right;
};

tree *recover(string a, string b) {
	tree *t = new tree;
	t->info = a[0];

	bool left = true;
	string lefta, leftb, righta, rightb;
	for (int i = 0; i < (int)b.size(); i++) {
		if (b[i] == a[0])
			left = false;
		else if (left)
			lefta.push_back(a[i + 1]), leftb.push_back(b[i]);
		else
			righta.push_back(a[i]), rightb.push_back(b[i]);
	}
	
	if (lefta.size() != 0)
		t->left = recover(lefta, leftb);
	else
		t->left = NULL;
	if (righta.size() != 0)
		t->right = recover(righta, rightb);
	else
		t->right = NULL;
	return t;
}

void posfix(tree *t) {
	if (t != NULL) {
		posfix(t->left);
		posfix(t->right);
		cout << t->info;
	}
}

void destroy(tree *t) {
	if (t != NULL) {
		destroy(t->left);
		destroy(t->right);
		delete t;
	}
}

int main() {
	string a, b;

	while (cin >> a >> b) {
		tree *t = recover(a, b);
		posfix(t);
		cout << endl;
		destroy(t);
	}

	return 0;
}
