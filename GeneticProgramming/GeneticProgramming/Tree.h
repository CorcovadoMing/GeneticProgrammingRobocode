#pragma once
#include "Node.h"
#include <string>

class Tree
{
public:
	Tree(const std::string &);
	
	const Node *root() const { return &root_; }
	Node *root() { return &root_; }
	
	//void parse() const;

private:
	Node root_;
};