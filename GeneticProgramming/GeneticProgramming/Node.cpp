#include "Node.h"
#include <map>
#include <iostream>

Node::Node(const std::string &type) : type_(type)
{
	std::vector<std::string> syntax = Node::GrowthRule(type);
	for (const std::string i : syntax)
	{
		child_.push_back(i);
	}
}

const std::vector<std::string> &Node::GrowthRule(const std::string &type)
{
	static std::map< std::string, std::vector<std::string> > Rule;
	Rule["ifstatement"] = std::vector<std::string> {"boolexpression", "statements", "statements"};
	Rule["boolexpression"] = std::vector<std::string> {"null"};
	Rule["statements"] = std::vector<std::string> {"null"};
	Rule["null"] = std::vector<std::string>();
	
	return Rule[type];
}

const std::size_t Node::numberOfChildren() const 
{ 
	return child_.size(); 
}

void Node::addChild(const Node &child) 
{ 
	child_.push_back(child); 
}

void Node::addChild(const std::string &child)
{
	child_.push_back(Node(child));
}

const Node *Node::child(const std::size_t index) const 
{ 
	return &child_[index]; 
}

Node *Node::child(const std::size_t index) 
{ 
	return &child_[index]; 
}

const std::string &Node::getData() const 
{ 
	return data_; 
}

const std::string &Node::getType() const
{
	return type_;
}