#include "Tree.h"
#include <iostream>

int main()
{
	Tree tree("ifstatement");
	std::cout << tree.root().getData() << std::endl;
	std::cout << tree.root().numberOfChildren() << std::endl;
	tree.root().addChild(Node("boolExpression"));
	std::cout << tree.root().numberOfChildren() << std::endl;
	std::cout << tree.root().child(0).getData() << std::endl;

	return 0;
}