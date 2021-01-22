#include <bits/stdc++.h>


using namespace std;

int first;

struct tree {
	char info;
	tree *left;
	tree *right;
};

tree *insert(tree *t, char value) {
	if (t == NULL) {
		t = new tree;
		t->info = value;
		t->left = t->right = NULL;
	}
	else if (value < t->info)
		t->left = insert(t->left, value);
	else
		t->right = insert(t->right, value);
	
	return t;
}

bool search(tree *t, char value) {
	if (t != NULL) {
		if (t->info == value)
			return true;
		else if (value < t->info)
			return search(t->left, value);
		else
			return search(t->right, value);
	}
	else
		return false;
}

void prefix(tree *t) {
	if (t != NULL) {
		if (first++ == 0)
			cout << t->info;
		else
			cout << " " << t->info;
		prefix(t->left);
		prefix(t->right);
	}
}

void posfix(tree *t) {
	if (t != NULL) {
		posfix(t->left);
		posfix(t->right);
		if (first++ == 0)
			cout << t->info;
		else
			cout << " " << t->info;
	}
}

void infix(tree *t) {
	if (t != NULL) {
		infix(t->left);
		if (first++ == 0)
			cout << t->info;
		else
			cout << " " << t->info;
		infix(t->right);
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
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	tree *t = NULL;
	char value;
	string command;

	while (cin >> command) {
		if (command == "I") {
			cin >> value;
			t = insert(t, value);
		}
		else if (command == "P") {
			cin >> value;
			if (search(t, value))
				cout << value << " existe\n";
			else
				cout << value << " nao existe\n";
		}
		else if (command == "INFIXA")
			first = 0, infix(t), cout << endl;
		else if (command == "PREFIXA")
			first = 0, prefix(t), cout << endl;
		else if (command == "POSFIXA")
			first = 0, posfix(t), cout << endl;
	}
	destroy(t);

	return 0;
}
