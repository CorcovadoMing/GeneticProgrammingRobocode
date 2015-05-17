#include "Tree.h"
#include <iostream>

int main()
{
	Tree tree("expression", 0);
	tree.parse();
	std::cout << std::endl;

	/*
	std::cout << "Original: " << std::endl;
	tree.parse();
    
    tree.exportTo("1.txt");

	Tree another_tree("flowStatement", 0);
	
	std::cout << std::endl << "Another Tree:" << std::endl;
	another_tree.parse();

	another_tree.importFrom("1.txt");
	std::cout << std::endl << "After import:" << std::endl;
	another_tree.parse();
	//std::swap(*another_tree_root->child(0), *root->child(0));
	std::cout << std::endl;
	*/
	tree.print();
	return 0;
}