#include "Tree.h"
#include <iostream>

Tree::Tree(const std::string &type, const int level) : root_(type, level)
{
}

void Tree::print() const
{
	std::cout << "[Root " << root_.getLevel() << "] " << root_.getType() << " " << root_.willExpand() << std::endl;
	for (std::size_t i = 0; i < root_.numberOfChildren(); i += 1)
	{
		print(root_.child(i));
	}
}

void Tree::print(const Node *node) const
{
	const std::string space = "  ";
	for (std::size_t i = 0; i < node->getLevel(); i += 1)
	{
		std::cout << space;
	}
	std::cout << "[Node " << node->getLevel() << "] " << node->getType() << " " << node->willExpand() << std::endl;
	for (std::size_t i = 0; i < node->numberOfChildren(); i += 1)
	{
		print(node->child(i));
	}
}

void Tree::parse() const
{
	if (root_.willExpand())
	{
		std::cout << root_.getType() << std::endl;
	}
	for (std::size_t i = 0; i < root_.numberOfChildren(); i += 1)
	{
		parse(root_.child(i));
	}
}

void Tree::parse(const Node *node) const
{
	if (node->willExpand())
	{
		std::cout << node->getType() << std::endl;
	}
	for (std::size_t i = 0; i < node->numberOfChildren(); i += 1)
	{
		parse(node->child(i));
	}
}

