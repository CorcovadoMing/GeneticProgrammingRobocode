#include "Node.h"

Node::Node(const std::string &data) : data_(data)
{
}

const std::size_t Node::numberOfChildren() const 
{ 
	return child_.size(); 
}

void Node::addChild(const Node &child) 
{ 
	child_.push_back(child); 
}

const Node &Node::child(const std::size_t index) const 
{ 
	return child_[index]; 
}

Node &Node::child(const std::size_t index) 
{ 
	return child_[index]; 
}

void Node::setData(std::string & data) 
{ 
	data_ = data; 
}

const std::string &Node::getData() const 
{ 
	return data_; 
}