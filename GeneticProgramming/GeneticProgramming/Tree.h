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
	void parse() const;

private:
	void print(const Node *) const;
	void parse(const Node *, const bool withNewLine=true, int indent=0) const;
	Node root_;
};