#ifndef RED_BLACK_TREE_H_
#define RED_BLACK_TREE_H_

#include "Node.h"
#include <deque>
#include <vector>
#include <iostream>

class RedBlackTree {
public:
	long size;

	RedBlackTree();
	~RedBlackTree();
	void insert(float key, long content);
	void retrieve(std::vector<long> &res, float first, float last);

private:
	Node *root;
	long trackSize;
	std::deque<Node*> trackRecord;

	void rebalance();
	void keepTrack(Node *n);
	Node *dequeueTrack();
	void insert(Node *n, float key, long content);
	void retrieve(Node *n, std::vector<long> &res, float first, float last);
};

#endif

