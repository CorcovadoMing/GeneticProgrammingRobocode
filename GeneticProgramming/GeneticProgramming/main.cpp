#include "Tree.h"
#include <iostream>

int main()
{
	Tree tree("statements", 0);

	tree.print();

	std::cout << std::endl << "=== Parse Code ===" << std::endl << std::endl;

	tree.parse();
	//std::swap(*another_tree_root->child(0), *root->child(0));
	std::cout << std::endl;
	return 0;
}