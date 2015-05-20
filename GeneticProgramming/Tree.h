#pragma once
#include <string>
#include "Node.h"

typedef std::vector<std::vector<std::string> > Table;

class Tree
{
public:
	Tree(const std::string &, const int, const int);
	const Node *root() const { return &root_; }
	Node *root() { return &root_; }
	void print() const;
	void parse();
	void exportTo(const char *) const;
	void fprint(std::ofstream &, const Node *) const;
	void importFrom(const char *);
	void fscan(std::ifstream &, Node *);
	const int getGPno() const { return GP_no_; }
	void setGPno(const int GP_no) { GP_no_ = GP_no; }
private:
	void print(const Node *) const;
	void parse(Node *, const bool withNewLine = true, int indent = 0);
	Node root_;
	int GP_no_;

	static const std::string &randomVariable(const int);
	static const std::string &randomArgumentRequiring0(const int);
	static const std::string &randomArgumentRequiring1(const int);
};