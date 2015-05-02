#include "Tree.h"
#include <iostream>

Tree::Tree(const std::string &type) : root_(type)
{
}

void Tree::print() const
{
	std::cout << "[Root] " << root_.getType() << std::endl;
	for (std::size_t i = 0; i < root_.numberOfChildren(); i += 1)
	{
		printSubtree(root_.child(i), 1);
	}
}

void Tree::printSubtree(const Node *node, const int level) const
{
	const std::string space = "  ";
	for (std::size_t i = 0; i < level; i += 1)
	{
		std::cout << space;
	}

	std::cout << "[Node] " << node->getType() << std::endl;
	for (std::size_t i = 0; i < node->numberOfChildren(); i += 1)
	{
		printSubtree(node->child(i), level + 1);
	}
}