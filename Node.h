#pragma once

using namespace std;

class Node
{
	int value;
	bool color;	//���� ��� ������-������� ������, true - ������, false - �������
	Node *parent;
	Node *left;
	Node *right;

public:
	Node();
	Node(int _value);
	Node(int _value, bool _color, Node *_parent, Node *_left, Node *_right);
	~Node();

};

