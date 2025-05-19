#include "RedBlackTree.h"

void RedBlackTree::fixRemove(Node *& _node)
{
}

void RedBlackTree::rotateLeft(Node *& _node)
{
}

void RedBlackTree::rotateRight(Node *& _node)
{
}

RedBlackTree::RedBlackTree()
{
}

void RedBlackTree::fixAdd(Node*& _currentNode)
{
	Node* node = _currentNode;
	Node* parent = nullptr;
	Node* grandparent = nullptr;
	while (node != root && node->isRed
		&& node->parent->isRed) {
		parent = node->parent;
		grandparent = parent->parent;
		if (parent == grandparent->left) 
		{
			Node* uncle = grandparent->right;
			if (uncle != nullptr
				&& uncle->isRed) 
			{
				grandparent->isRed = true;
				parent->isRed = false;
				uncle->isRed = false;
				node = grandparent;
			}
			else 
			{
				if (node == parent->right) 
				{
					rotateLeft(parent);
					node = parent;
					parent = node->parent;
				}
				rotateRight(grandparent);

				bool _temp = parent->isRed;
				parent->isRed = grandparent->isRed;
				grandparent->isRed = _temp;
				node = parent;
			}
		}
		else {
			Node* uncle = grandparent->left;
			if (uncle != nullptr
				&& uncle->isRed) {
				grandparent->isRed = true;
				parent->isRed = false;
				uncle->isRed = false;
				node = grandparent;
			}
			else {
				if (node == parent->left) {
					rotateRight(parent);
					node = parent;
					parent = node->parent;
				}
				rotateLeft(grandparent);
				swap(parent->isRed, grandparent->isRed);
				node = parent;
			}
		}
	}
	root->isRed = false;
}


void RedBlackTree::add(int _value)
{
	Node* _current = root;
	Node* _node = new Node(_value);
	Node* _parent = nullptr;

	while (_current != nullptr) 
	{
		_parent = _current;
		if (_parent->value < _node->value) 
		{
			_current = _parent->left;
		}
		else 
		{
			_current = _parent->right;
		}

	}

	if (_parent == nullptr)
	{
		root = _node;
	}

	else if(_parent->value < _node->value) 
	{
		_parent->left = _node;
		fixAdd(_node);
	}
	else
	{
		_parent->right = _node;
		fixAdd(_node);
	}



}

void RedBlackTree::remove(int _value)
{
}

bool RedBlackTree::contains(int _value)
{
	return false;
}

void RedBlackTree::deleteTree()
{
}

void RedBlackTree::printInfo()
{
}

RedBlackTree::~RedBlackTree()
{
}
