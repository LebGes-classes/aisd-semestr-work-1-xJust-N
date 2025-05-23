#include <iostream>
#include <cstdlib>
#include <ctime>

#include "RedBlackTree.h"

int main()
{
	srand(time(0));
	RedBlackTree* rbt = new RedBlackTree();

	int elementsCount = 10 + rand() % 30;

	for (int i = 0; i < elementsCount; i++)
	{
		rbt->add(rand() % 100);
	}
	rbt->printInfo();

	system("pause");
	return 0;
}