#pragma once

using namespace std;

struct Node
{
public:
	int value;
	bool isRed;	//���� ��� ������-������� ������, true - �������, false - ������
	Node *parent;
	Node *left;
	Node *right;

	Node(int _value);
	Node(int _value, bool _color, Node *_parent, Node *_left, Node *_right);
	~Node();

};

