#pragma once
#include <string>
#include <vector>

class Node
{
public:
	Node(const std::string &);
	const std::size_t numberOfChildren() const;
	void addChild(const Node &);
	const Node &child(const std::size_t) const;
	Node &child(const std::size_t);
	void setData(std::string &);
	const std::string &getData() const;
private:
	std::string data_;
	std::string type_;
	std::vector<Node> child_;
};
