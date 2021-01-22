#include <bits/stdc++.h>


using namespace std;

struct tree {
	int info;
	tree *left;
	tree *right;
};

tree *insert(tree *t, int value) {
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

void prefix(tree *t) {
	if (t != NULL) {
		printf(" %d", t->info);
		prefix(t->left);
		prefix(t->right);
	}
}

void posfix(tree *t) {
	if (t != NULL) {
		posfix(t->left);
		posfix(t->right);
		printf(" %d", t->info);
	}
}

void infix(tree *t) {
	if (t != NULL) {
		infix(t->left);
		printf(" %d", t->info);
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
	tree *t = NULL;
	int C, N, aux;

	scanf("%d", &C);
	for (int i = 0; i < C; i++) {
		scanf("%d", &N);
		while (N--)
			scanf("%d", &aux), t = insert(t, aux);
		printf("Case %d:\n", i + 1);

		printf("Pre.:");
		prefix(t);
		printf("\n");

		printf("In..:");
		infix(t);
		printf("\n");

		printf("Post:");
		posfix(t);
		printf("\n\n");

		destroy(t);
		t = NULL;
	}

	return 0;
}
