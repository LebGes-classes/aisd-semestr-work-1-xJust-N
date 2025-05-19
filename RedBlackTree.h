#pragma once

#include "Node.h"

class RedBlackTree
{
	Node *root;

private:
	void fixAdd(Node*& _node);
	void fixRemove(Node*& _node);
	void rotateLeft(Node*& _node);
	void rotateRight(Node*& _node);
public:
	RedBlackTree();
	void add(int _value);
	void remove(int _value);
	bool contains(int _value);
	void deleteTree();
	void printInfo();
	~RedBlackTree();
};

