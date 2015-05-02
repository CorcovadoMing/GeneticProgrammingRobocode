#include "Node.h"
#include <map>
#include <iostream>

Node::Node(const std::string &data) : data_(data), type_(Node::DataToType(data))
{
}

const std::string &Node::DataToType(const std::string &data)
{
	static std::map<std::string, std::string> Table;
	Table["if"] = "ifstatement";

	return Table[data];
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

void Node::setData(std::string & data) 
{ 
	data_ = data; 
	type_ = Node::DataToType(data);
}

const std::string &Node::getData() const 
{ 
	return data_; 
}

const std::string &Node::getType() const
{
	return type_;
}