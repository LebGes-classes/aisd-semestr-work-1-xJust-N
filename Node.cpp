#pragma once

#include "Node.h"

Node::Node(int _value)
{
	this->value = _value;
}

Node::Node(int _value, bool _color, Node *_parent, Node *_left, Node *_right)
{
	this->value = _value;
	this->isRed = _color;
	this->parent = _parent;
}
Node :: ~Node()
{
	delete this;
}
