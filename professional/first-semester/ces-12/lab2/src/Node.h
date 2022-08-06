#ifndef NODE_H_
#define NODE_H_

#include "Color.h"

class Node {
public:
	Color color;
	Node *left;
	Node *right;
	float key;

	Node();
	Node(Color color, float key, long content);
	Node(Node *left, Node *right, Color color, float key, long content);
	~Node();
	Node *compare(float query);
	void attach(Node *son);
	long getIdx();

private:
	long content;
};

#endif

