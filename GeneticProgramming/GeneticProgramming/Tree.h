#pragma once
#include <string>
#include <vector>

class Node
{
public:
	Node(const std::string &data) { data_ = data; }
	
	const std::size_t numberOfChildren() const { return child_.size(); }
	void addChild(const Node &child) { child_.push_back(child); }
	const Node &child(const std::size_t index) const { return child_[index]; }
	Node &child(const std::size_t index) { return child_[index]; }
	void setData(std::string & data) { data_ = data; }
	const std::string &getData() const { return data_; }
private:
	std::string data_;
	std::string type_;
	std::vector<Node> child_;
};


class Tree
{
public:
	Tree(const std::string &);
	const Node &root() const { return root_; }
	Node &root() { return root_; }
private:
	Node root_;
};