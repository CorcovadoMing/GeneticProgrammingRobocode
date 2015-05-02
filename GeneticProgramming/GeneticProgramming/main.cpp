#include "Tree.h"
#include <iostream>

int main()
{
	Tree tree("if");
	Node* root = tree.root();
	
	root->addChild("if");
	Node *current_node = root->child(0);

	root->addChild("not");

	Tree another_tree("equal");
	Node*another_tree_root = another_tree.root();

	another_tree_root->addChild("not");


	std::cout << "[Before] First tree root: " << root->getData() << " " << root->getType() << std::endl;
	std::cout << root->child(0)->getData() << " " << root->child(0)->getType() << std::endl;
	std::cout << root->child(1)->getData() << " " << root->child(1)->getType() << std::endl << std::endl;
	std::cout << "[Before] Second tree root: " << another_tree_root->getData() << " " << another_tree_root->getType() << std::endl;
	std::cout << another_tree_root->child(0)->getData() << " " << another_tree_root->child(0)->getType() << std::endl << std::endl;

	std::swap(*another_tree_root->child(0), *root->child(0));

	std::cout << "[After] First tree root: " << root->getData() << " " << root->getType() << std::endl;
	std::cout << root->child(0)->getData() << " " << root->child(0)->getType() << std::endl;
	std::cout << root->child(1)->getData() << " " << root->child(1)->getType() << std::endl << std::endl;
	std::cout << "[After] Second tree root: " << another_tree_root->getData() << " " << another_tree_root->getType() << std::endl;
	std::cout << another_tree_root->child(0)->getData() << " " << another_tree_root->child(0)->getType() << std::endl;


	return 0;
}