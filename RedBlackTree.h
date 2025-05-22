#pragma once

#include "Node.h"

class RedBlackTree
{

public:
	RedBlackTree();
	void add(int _value);
	void remove(int _value);
	bool contains(int _value);
	void printInfo();
	~RedBlackTree();
};

