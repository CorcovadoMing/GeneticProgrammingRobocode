#include "Tree.h"
#include <iostream>

int main()
{
	Tree tree("if");
	Node* root = tree.root();
	
	std::cout << root->getData() << " " << root->getType() << std::endl;
	std::cout << root->numberOfChildren() << std::endl;
	
	root->addChild("if");
	Node *current_node = root->child(0);
	std::cout << root->numberOfChildren() << std::endl;
	std::cout << current_node->getData() << " " << current_node->getType() << std::endl;
	std::cout << current_node->numberOfChildren() << std::endl;

	return 0;
}