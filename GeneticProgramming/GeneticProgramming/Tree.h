#pragma once
#include "Node.h"
#include <string>

class Tree
{
public:
	Tree(const std::string &, const int);
	const Node *root() const { return &root_; }
	Node *root() { return &root_; }
	void print() const;
	void parse() const; //Tend to implement 2-pass parser

private:
	void print(const Node *) const;
	void parse(const Node *) const;
	Node root_;
};