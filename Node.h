#pragma once

using namespace std;

struct Node
{
	int value;
	bool isRed;	//÷вет дл€ красно-черного дерева, true - черный, false - красный
	Node *parent;
	Node *left;
	Node *right;

	Node(int _value);
	Node(int _value, bool _color, Node *_parent, Node *_left, Node *_right);
	~Node();

};

