#include "Tree.h"
#include <iostream>

int main()
{
	Tree tree("if");
	Node* root = &tree.root();
	
	std::cout << root->getData() << " " << root->getType() << std::endl;
	std::cout << root->numberOfChildren() << std::endl;
	
	root->addChild(Node("if"));
	std::cout << root->numberOfChildren() << std::endl;
	std::cout << root->child(0)->getData() << std::endl;

	return 0;
}