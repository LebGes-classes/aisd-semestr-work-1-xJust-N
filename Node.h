#pragma once

using namespace std;

class Node
{
	int value;
	bool color;	//÷вет дл€ красно-черного дерева, true - черный, false - красный
	Node *parent;
	Node *left;
	Node *right;

public:
	Node();
	Node(int _value);
	Node(int _value, bool _color, Node *_parent, Node *_left, Node *_right);
	~Node();

};

