#include "RedBlackTree.h"

RedBlackTree::RedBlackTree() {
	this->root = nullptr;
	this->trackSize = this->size = 0;
}

RedBlackTree::~RedBlackTree() {
	if (this->root != nullptr) {
		delete this->root;
	}
}

void RedBlackTree::insert(float key, long content) {
	if (this->root == nullptr) {
		this->root = new Node(Color::BLACK, key, content);
	} else {
		this->keepTrack(this->root);
		this->insert(this->root->compare(key), key, content);
		this->trackSize = 0;
	}

	this->size++;
}

void RedBlackTree::retrieve(std::vector<long> &res, float first, float last) {
	this->retrieve(this->root, res, first, last);
}

void RedBlackTree::rebalance() {
	Node *son = this->dequeueTrack();
	Node *parent = this->dequeueTrack();
	bool leftSon = (parent->left == son);

	if (parent->color == Color::BLACK) {
		return;
	} else {
		Node *grand = this->dequeueTrack();
		bool leftParent = (grand->left == parent);
		Node *uncle = (grand->left == parent ? grand->right : grand->left);

		if (uncle != nullptr and uncle->color == Color::RED) {
			parent->color = Color::BLACK;
			uncle->color = Color::BLACK;
			grand->color = Color::RED;
			if (trackSize > 1) {
				this->keepTrack(grand);
				this->rebalance();
			} else if (trackSize == 0) {
				grand->color = Color::BLACK;
			}
		} else {
			if (leftParent and leftSon) {
				grand->left = parent->right;
				parent->right = grand;

				parent->color = Color::BLACK;
				grand->color = Color::RED;
			} else if (not leftParent and leftSon) {
				grand->right = son->left;
				parent->left = son->right;
				son->left = grand;
				son->right = parent;

				son->color = Color::BLACK;
				grand->color = Color::RED;
			} else if (leftParent and not leftSon) {
				parent->right = son->left;
				grand->left = son->right;
				son->left = parent;
				son->right = grand;

				son->color = Color::BLACK;
				grand->color = Color::RED;
			} else {
				grand->right = parent->left;
				parent->left = grand;

				parent->color = Color::BLACK;
				grand->color = Color::RED;
			}

			if (trackSize == 0) {
				if ((leftParent and leftSon) or (not leftParent and not leftSon)) {
					this->root = parent;
				} else {
					this->root = son;
				}
			} else {
				Node *grandGrand = this->dequeueTrack();
				if ((leftParent and leftSon) or (not leftParent and not leftSon)) {
					grandGrand->attach(parent);
				} else {
					grandGrand->attach(son);
				}
			}
		}
	}
}

void RedBlackTree::keepTrack(Node *n) {
	if (this->trackSize < this->trackRecord.size()) {
		this->trackRecord[this->trackSize] = n;
	} else {
		this->trackRecord.push_back(n);
	}

	this->trackSize++;
}

Node *RedBlackTree::dequeueTrack() {
	return this->trackRecord[--this->trackSize];
}

void RedBlackTree::insert(Node *n, float key, long content) {
	if (n == nullptr) {
		n = new Node(Color::RED, key, content);
		this->trackRecord[this->trackSize - 1]->attach(n);
		this->keepTrack(n);
		this->rebalance();
	} else {
		this->keepTrack(n);
		this->insert(n->compare(key), key, content);
	}
}

void RedBlackTree::retrieve(Node *n, std::vector<long> &res, float first, float last) {
	if (n != nullptr) {
		if (first <= n->key) {
			retrieve(n->left, res, first, last);
		}
		if (first <= n->key and n->key <= last) {
			res.push_back(n->getIdx());
		}
		if (n->key <= last) {
			retrieve(n->right, res, first, last);
		}
	}
}

