#include "Tree.h"
#include <iostream>

int main()
{
	Tree tree("statements");
	std::cout << "Root\t\t" << tree.root()->getType() << std::endl;
	for (std::size_t i = 0; i < tree.root()->numberOfChildren(); i += 1)
	{
		std::cout << "Child[" << i << "]\t" << tree.root()->child(i)->getType() << std::endl;
		
		Node* current = tree.root()->child(i);
		for (std::size_t j = 0; j < current->numberOfChildren(); j += 1)
		{
			std::cout << "Sub-Child[" << j << "]\t" << current->child(j)->getType() << std::endl;
		}
	}

	//std::swap(*another_tree_root->child(0), *root->child(0));

	return 0;
}