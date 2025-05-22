#pragma once

#include "Node.h"

Node::Node(int _value)
	: value(_value),
	isRed(true),
	parent(nullptr),
	left(nullptr),
	right(nullptr)
{}

Node::Node(int _value, bool _color, Node* _parent, Node* _left, Node* _right)
	: value(_value),
	isRed(_color),
	parent(_parent),
	left(_left),
	right(_right)
{}
Node :: ~Node()
{}
