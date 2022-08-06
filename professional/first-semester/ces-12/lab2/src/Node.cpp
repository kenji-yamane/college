#include "Node.h"
#include <iostream>

Node::Node() {
	this->left = this->right = nullptr;
	this->color = Color::BLACK;
	this->key = 0.0;
	this->content = 0;
}

Node::Node(Color color, float key, long content) : color(color), key(key), content(content) {
	this->left = this->right = nullptr;
}

Node::Node(Node *left, Node *right, Color color, float key, long content) :
	left(left), right(right), color(color), key(key), content(content) {
}

Node::~Node() {
	if (this->left != nullptr) {
		delete this->left;
	}
	if (this->right != nullptr) {
		delete this->right;
	}
}

Node *Node::compare(float query) {
	if (query < this->key) {
		return this->left;
	} else {
		return this->right;
	}
}

void Node::attach(Node *son) {
	if (son->key < this->key) {
		this->left = son;
	} else {
		this->right = son;
	}
}

long Node::getIdx() {
	return this->content;
}

