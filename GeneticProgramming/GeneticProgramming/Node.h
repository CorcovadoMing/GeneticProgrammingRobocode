#pragma once
#include <string>
#include <vector>
#include <map>

class Node
{
public:
	Node(const std::string &);

	const std::size_t numberOfChildren() const;
	
	void addChild(const Node &);
	void addChild(const std::string &);
	
	const Node *child(const std::size_t) const;
	Node *child(const std::size_t);
	
	void setData(std::string &);
	const std::string &getData() const;
	const std::string &getType() const;
private:
	std::string data_;
	std::string type_;
	std::vector<Node> child_;

	static const std::string &DataToType(const std::string &);
};
