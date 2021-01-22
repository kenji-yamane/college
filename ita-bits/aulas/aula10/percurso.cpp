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

void bfs(tree *t) {
	queue<tree*> q;

	if (t != NULL)
		q.push(t);
	while (!q.empty()) {
		tree *aux = q.front();
		if (aux->left != NULL)
			q.push(aux->left);
		if (aux->right != NULL)
			q.push(aux->right);

		printf("%d%c", aux->info, q.size() == 1 ? '\n' : ' ');
		q.pop();
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
	int C, N, aux;
	tree *t = NULL;

	scanf("%d", &C);
	for (int i = 0; i < C; i++) {
		scanf("%d", &N);
		while (N--) {
			scanf("%d", &aux);
			t = insert(t, aux);
		}
		printf("Case %d:\n", i + 1);
		bfs(t);
		printf("\n");
		destroy(t);
		t = NULL;
	}

	return 0;
}
