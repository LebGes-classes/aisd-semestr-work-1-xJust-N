#pragma once

#include "Node.h"

class RedBlackTree
{
	Node *root;

public:
	RedBlackTree();
	void add(int _value);
	void remove(int _value);
	bool contains(int _value);
	void deleteTree();
	void printInfo();
	~RedBlackTree();
};

