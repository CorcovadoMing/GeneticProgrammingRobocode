#pragma once
#include "Node.h"
#include <string>

class Tree
{
public:
    Tree(const std::string &, const int, const int);
    const Node *root() const { return &root_; }
    Node *root() { return &root_; }
    void print() const;
    void parse() const;
    void exportTo(const char *) const;
    void fprint(std::ofstream &, const Node *) const;
    void importFrom(const char *);
    void fscan(std::ifstream &, Node *);
	const int getGPno() const { return GP_no_; }
private:
    void print(const Node *) const;
    void parse(const Node *, const bool withNewLine = true, int indent = 0) const;
    Node root_;
	const int GP_no_;
};