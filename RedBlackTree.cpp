#include <iostream>
#include <queue>
#include <string>

#include "RedBlackTree.h"


Node* root;

//Методы поворота для балансировки
void rotateLeft(Node *& node)
{
	Node* child = node->right;

	node->right = child->left;
	child->left = node;

	if (node->right != nullptr)
		node->right->parent = node;

	//Обновление ссылок для родителей
	if (node->parent == nullptr)
		root = child;
	else if (node == child->parent->left)
		node->parent->left = child;
	else 
		node->parent->right = child;

	child->parent = node->parent;
	node->parent = child;
}

void rotateRight(Node *& node)
{
	Node* child = node->left;

	node->left = child->right;
	child->right = node;

	if (node->left != nullptr)
		node->left->parent = node;

	//Обновление ссылок для родителей
	if (node->parent == nullptr)
		root = child;
	else if (node == child->parent->left)
		node->parent->left = child;
	else
		node->parent->right = child;

	child->parent = node->parent;
	node->parent = child;
}

//Свап цветов - при двух красных потомках родитель становится красным
void colorSwap(Node*& parent) {


	Node* left = parent->left;
	Node* right = parent->right;

	if (parent != nullptr && left != nullptr && right != nullptr &&
		left->isRed && right->isRed && parent != root)
	{
		left->isRed = false;
		right->isRed = false;
		parent->isRed = true;
	}
}

//Метод для устранения нарушения баланса
void fixAdd(Node*& currentNode)
{
	Node* node = currentNode;
	Node* parent = nullptr;
	Node* grandparent = nullptr;
	//балансировка нужна тогда и только тогда если два идущих подряд узла - красные
	while (node != root && node->isRed
		&& node->parent->isRed) {
		parent = node->parent;
		grandparent = parent->parent;
		if (grandparent != nullptr && parent == grandparent->left)
		{
			Node* uncle = grandparent->right;

			//Родитель и дядя красные - свап цветов
			if (uncle != nullptr
				&& uncle->isRed)
			{
				colorSwap(grandparent);
				node = grandparent;
			}
			else
			{
				//Родитель левый и его ребенок справа
				if (node == parent->right)
				{
					rotateLeft(parent);
					node = parent;
					parent = node->parent;
				}
				//Родитель левый и его ребенок слева
				rotateRight(grandparent);

				swap(parent->isRed, grandparent->isRed);
				node = parent;
			}
		}
		else if(grandparent != nullptr)
		{
			Node* uncle = grandparent->left;
			//Родитель и дядя красные - свап цветов
			if (uncle != nullptr
				&& uncle->isRed) {
				colorSwap(grandparent);
				node = grandparent;
			}
			else {
				//Родитель правый и его ребенок слева
				if (node == parent->left) {
					rotateRight(parent);
					node = parent;
					parent = node->parent;
				}
				//Родитель правый и его ребенок справа
				rotateLeft(grandparent);
				swap(parent->isRed, grandparent->isRed);
				node = parent;
			}
		}
	}
	root->isRed = false;
}

//Вспомогательные методы для удаления
void transplant(Node*& root, Node*& u, Node*& v)
{
	if (u->parent == nullptr)
		root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	if (v != nullptr)
		v->parent = u->parent;
}

Node* minValueNode(Node*& node)
{
	Node* current = node;
	while (current->left != nullptr)
		current = current->left;

	return current;
}

void fixRemove(Node*& node)
{
	while (node != root && node->isRed == false) 
	{
		if (node == node->parent->left) 
		{
			Node* sibling = node->parent->right;
			if (sibling->isRed) 
			{
				sibling->isRed = false;
				node->parent->isRed = true;
				rotateLeft(node->parent);
				sibling = node->parent->right;
			}
			if ((sibling->left == nullptr || sibling->left->isRed == false) && (sibling->right == nullptr || sibling->right->isRed == false)) 
			{
				sibling->isRed = true;
				node = node->parent;
			}
			else
			{
				if (sibling->right == nullptr || sibling->right->isRed == false) 
				{				
					if (sibling->left != nullptr)
						sibling->left->isRed = false;

					sibling->isRed = true;
					rotateRight(sibling);
					sibling = node->parent->right;
				}
				sibling->isRed = node->parent->isRed;
				node->parent->isRed = false;
				if (sibling->right != nullptr)
					sibling->right->isRed = false;

				rotateLeft(node->parent);
				node = root;
			}
		}
		else 
		{
			Node* sibling = node->parent->left;

			if (sibling->isRed) 
			{
				sibling->isRed = false;
				node->parent->isRed = true;
				rotateRight(node->parent);
				sibling = node->parent->left;
			}
			if ((sibling->left == nullptr || sibling->left->isRed == false) && (sibling->right == nullptr || sibling->right->isRed == false)) 
			{
				sibling->isRed = true;
				node = node->parent;
			}
			else 
			{
				if (sibling->left == nullptr || sibling->left->isRed == false)
				{
					if (sibling->right != nullptr)
						sibling->right->isRed = false;

					sibling->isRed = true;
					rotateLeft(sibling);
					sibling = node->parent->left;
				}
				sibling->isRed = node->parent->isRed;
				node->parent->isRed = false;
				if (sibling->left != nullptr)
					sibling->left->isRed = false;

				rotateRight(node->parent);
				node = root;
			}
		}
	}
	node->isRed = false;
}

//Рекурсивно удаляет узлы
void deleteTree(Node*& node)
{
	if (node != nullptr)
	{
		deleteTree(node->left);
		deleteTree(node->right);
		delete node;
	}
}


//Универсальный метод для поиска
Node* findNodeWithValue(int value)
{
	Node* current = root;
	bool flag = true;
	while (flag && current != nullptr) 
	{
		if (current->value == value)
			flag = false;
		else if (current->value < value)
			current = current->left;
		else
			current = current->right;
	}

	return current;
}

//Поиск высоты используя очередь
int findHeight(Node* root) {
	if (root == nullptr) 
		return -1;

	queue<Node*> q;
	q.push(root);
	int height = -1;

	while (!q.empty()) 
	{
		int levelSize = q.size();
		height++;

		for (int i = 0; i < levelSize; i++) 
		{
			Node* current = q.front();
			q.pop();

			if (current->left != nullptr)
				q.push(current->left);
			if (current->right != nullptr)
				q.push(current->right);
		}
	}
	return height;
}

//Рекурсивный метод для вывода в консоль
void printHelper(Node* root, string indent, bool last)
{
	if (root != nullptr) 
	{
		cout << (indent);
		if (last) 
		{
			cout << "R----";
			indent += "   ";
		}
		else 
		{
			cout << "L----";
			indent += "|  ";
		}

		cout << root->value << "(" << ((root->isRed) ? "RED" : "BLACK") << ")" << endl;

		printHelper(root->left, indent, false);
		printHelper(root->right, indent, true);
	}
}







//Реализация интерфейса:
RedBlackTree::RedBlackTree()
{
	root = nullptr;
}

void RedBlackTree::add(int value)
{
	Node* node = new Node(value);
	Node* parent = nullptr;
	Node* current = root;
	
	//Поиск нужного листа
	while (current != nullptr) {
		parent = current;
		if (node->value < current->value)
			current = current->left;
		else
			current = current->right;
	}
	node->parent = parent;

	//Привязка к родителям:
	if (parent == nullptr)
	{
		root = node;
		fixAdd(node);
	}
	else if (node->value < parent->value)
	{
		parent->left = node;
	}
	else
	{
		parent->right = node;
		fixAdd(node);
	}
}



void RedBlackTree::remove(int value)
{
	Node* nodeToDelete = findNodeWithValue(value);

	if (nodeToDelete == nullptr)
	{
		cout << "Элемент не найден" << endl;
		return;
	}

	Node* x = nullptr;
	Node* y = nullptr;


	y = nodeToDelete;
	bool yIsRed = y->isRed;
	if (nodeToDelete->left == nullptr) 
	{
		x = nodeToDelete->right;
		transplant(root, nodeToDelete, nodeToDelete->right);
	}
	else if (nodeToDelete->right == nullptr) 
	{
		x = nodeToDelete->left;
		transplant(root, nodeToDelete, nodeToDelete->left);
	}
	else 
	{
		y = minValueNode(nodeToDelete->right);
		yIsRed = y->isRed;
		x = y->right;
		if (y->parent == nodeToDelete) 
		{
			if (x != nullptr)
				x->parent = y;
		}
		else 
		{
			transplant(root, y, y->right);
			y->right = nodeToDelete->right;
			y->right->parent = y;
		}
		transplant(root, nodeToDelete, y);
		y->left = nodeToDelete->left;
		y->left->parent = y;
		y->isRed = nodeToDelete->isRed;
	}
	delete nodeToDelete;
	if (yIsRed == false) 
	{
		fixRemove(x);
	}
}


bool RedBlackTree::contains(int value)
{
	return findNodeWithValue(value) != nullptr;
}


void RedBlackTree::printInfo()
{

	if (root == nullptr)
		cout << "Tree is empty." << endl;
	else 
	{
		cout << "Red-Black Tree:" << endl;
		cout << "Height :" << findHeight(root) << endl;
		printHelper(root, "", true);
	}
}

RedBlackTree::~RedBlackTree()
{
	deleteTree(root);
}
