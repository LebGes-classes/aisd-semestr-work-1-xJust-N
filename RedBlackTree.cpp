#include <iostream>
#include <vector>
#include "RedBlackTree.h"

using namespace std;

Node* root;

void fixRemove(Node *& _node)
{
}

void rotateLeft(Node *& _node)
{
	Node* _child = _node->right;

	_node->right = _child->left;
	_child->left = _node;

	if (_node->right != nullptr)
		_node->right->parent = _node;

	//Обновление ссылок для родителей
	if (_node->parent == nullptr)
		root = _child;
	else if (_node == _child->parent->left)
		_node->parent->left = _child;
	else 
		_node->parent->right = _child;

	_child->parent = _node->parent;
	_node->parent = _child;
}

void rotateRight(Node *& _node)
{
	Node* _child = _node->left;

	_node->left = _child->right;
	_child->right = _node;

	if (_node->left != nullptr)
		_node->left->parent = _node;

	//Обновление ссылок для родителей
	if (_node->parent == nullptr)
		root = _child;
	else if (_node == _child->parent->left)
		_node->parent->left = _child;
	else
		_node->parent->right = _child;

	_child->parent = _node->parent;
	_node->parent = _child;
}

void colorSwap(Node*& _parent) {
	//Свап цветов - при двух красных потомках родитель становится красным

	Node* _left = _parent->left;
	Node* _right = _parent->right;

	if (_parent != nullptr && left != nullptr && _right != nullptr &&
		_left->isRed && _right->isRed && _parent != root)
	{
		_left->isRed = false;
		_right->isRed = false;
		_parent->isRed = true;
	}
}

void fixAdd(Node*& _currentNode)
{
	Node* _node = _currentNode;
	Node* _parent = nullptr;
	Node* _grandparent = nullptr;
	//балансировка нужна тогда и только тогда если два идущих подряд узла - красные
	while (_node != root && _node->isRed
		&& _node->parent->isRed) {
		_parent = _node->parent;
		_grandparent = _parent->parent;
		if (_parent == _grandparent->left)
		{
			Node* _uncle = _grandparent->right;

			//Родитель и дядя красные - свап цветов
			if (_uncle != nullptr
				&& _uncle->isRed)
			{
				colorSwap(_grandparent);
				_node = _grandparent;
			}
			else
			{
				//Родитель левый и его ребенок справа
				if (_node == _parent->right)
				{
					rotateLeft(_parent);
					_node = _parent;
					_parent = _node->parent;
				}
				//Родитель левый и его ребенок слева
				rotateRight(_grandparent);

				swap(_parent->isRed, _grandparent->isRed);
				_node = _parent;
			}
		}
		else {
			Node* _uncle = _grandparent->left;
			//Родитель и дядя красные - свап цветов
			if (_uncle != nullptr
				&& _uncle->isRed) {
				colorSwap(_grandparent);
				_node = _grandparent;
			}
			else {
				//Родитель правый и его ребенок слева
				if (_node == _parent->left) {
					rotateRight(_parent);
					_node = _parent;
					_parent = _node->parent;
				}
				//Родитель правый и его ребенок справа
				rotateLeft(_grandparent);
				swap(_parent->isRed, _grandparent->isRed);
				_node = _parent;
			}
		}
	}
	root->isRed = false;
}

void fixRemove(Node*& _node)
{

}

Node* findNodeWithValue(int _value)
{
	Node* _current = root;
	bool _flag = true;
	while (_flag && _current != nullptr) 
	{
		if (_current->value == _value)
			_flag = false;
		else if (_current->value < _value)
			_current = _current->left;
		else
			_current = _current->right;
	}

	return _current;
}

int findHeight(Node* root) {
	if (root == nullptr) {
		return -1;
	}

	int leftHeight = findHeight(root->left);
	int rightHeight = findHeight(root->right);

	if (leftHeight > rightHeight)
		return leftHeight + 1;

	return rightHeight + 1;
}

void print(char c, int count)
{
	for (int i = 0; i < count; i++)
		cout << c;
}

void print(Node*& _node)
{
	if (_node != nullptr)
		cout << (_node->isRed) ? 'R' : 'B' << '(' << _node->value << ')';
	else
		print(' ', 5);
}

void print(Node*& _node, int _height)
{
	vector<Node*> _v;
	_v.push_back(_node);
	int _emptyLine = _height * 5;

	//Цикл для вывода
	for (int i = 0; i < _height; i++)
	{
		print(' ', _emptyLine);
		for (int j = 0; j < pow(2, i); j++)
		{
			Node* _node = _v.pop_back;

			print(_node);

			if (_node != nullptr)
			{
				_v.insert(_v.begin, _node->left);
				_v.insert(_v.begin, _node->right);
			}
		}
		cout << endl;
		_emptyLine -= 5;

	}
	_v.clear;
	delete &_v;
}

//Рекурсивно удаляет узлы
void deleteTree(Node*& _node)
{
	if (_node != nullptr)
	{
		deleteTree(_node->left);
		deleteTree(_node->right);
		delete _node;
	}
}



//Реализация интерфейса:
RedBlackTree::RedBlackTree()
{
	root = nullptr;
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
	}
	else
	{
		_parent->right = _node;
	}
	
	fixAdd(_node);
}

void RedBlackTree::remove(int _value)
{

}

bool RedBlackTree::contains(int _value)
{
	return findNodeWithValue(_value) != nullptr;
}


void RedBlackTree::printInfo()
{
	if (root == nullptr)
		cout << "Tree is empty." << endl;
	else {
		cout << "Red-Black Tree:" << endl;
		print(root, findHeight(root));
	}
}

RedBlackTree::~RedBlackTree()
{
	deleteTree(root);
}
