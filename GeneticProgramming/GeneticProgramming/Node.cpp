#include "Node.h"
#include "RandomRange.h"
#include <map>
#include <iostream>

Node::Node(const std::string &type, const int level) : type_(type), level_(level)
{
	// Growth
	if (level < 5)
	{
		Ruleset syntax = Node::GrowthRule(type);
		if (syntax.size())
		{
			const std::size_t index = RandomRange::random<int>(0, syntax.size() - 1);
			need_expand_ = (syntax[index][0] == "Expand" ? true : false);
			for (std::size_t i = 1; i < syntax[index].size(); i += 1)
			{
				if (syntax[index][i] != "null")
				{
					child_.push_back(Node(syntax[index][i], level + 1));
				}
			}
		}
	}
	// Terminal
	else
	{
		Ruleset syntax = Node::TerminalRule(type);
		if (syntax.size())
		{
			const std::size_t index = RandomRange::random<int>(0, syntax.size() - 1);
			need_expand_ = (syntax[index][0] == "Expand" ? true : false);
			for (std::size_t i = 1; i < syntax[index].size(); i += 1)
			{
				if (syntax[index][i] != "null")
				{
					child_.push_back(Node(syntax[index][i], level + 1));
				}
			}
		}
	}
}

const Ruleset &Node::GrowthRule(const std::string &type)
{
	static std::map<std::string, Ruleset> Rule;
	Rule["statements"] = Ruleset{ { "Transform", "statement", "statements", "controlStatement" }, { "Transform", "statement" } };
	Rule["statement"] = Ruleset{ { "Transform", "controlStatement" }, { "Transform", "argumentRequiring0" }, { "Transform", "argumentRequiring1"} };
	Rule["controlStatement"] = Ruleset{ { "Transform", "flowStatement" } };
	Rule["flowStatement"] = Ruleset{ { "Transform", "whileStatement" }, { "Transform", "ifStatement" } };
	Rule["ifStatement"] = Ruleset{ { "Transform", "ifStatement", "elseIfStatement" }, { "Expand", "conditionalExpression", "statements" } };
	Rule["elseIfStatement"] = Ruleset{ { "Transform", "elseIfStatement", "elseIfStatement" }, { "Transform", "elseIfStatement", "elseStatement" }, { "Expand", "conditionalExpression", "statements" } };
	// Semi-terminals
	Rule["whileStatement"] = Ruleset{ { "Expand", "conditionalExpression", "statements" } };
	// Terminals Zero-way
	Rule["argumentRequiring0"] = Ruleset{ { "Expand", "null" } };
	// Termninals One-way
	Rule["elseStatement"] = Ruleset{ { "Expand", "statements" } };
	Rule["argumentRequiring1"] = Ruleset{ { "Expand", "expression" } }; // issue
	Rule["expression"] = Ruleset{ { "Expand", "null" } }; // issue
	Rule["conditionalExpression"] = Ruleset{ { "Expand", "null" } }; // issue
	return Rule[type];
}

const Ruleset &Node::TerminalRule(const std::string &type)
{
	static std::map<std::string, Ruleset> Terminal;
	Terminal["statements"] = Ruleset{ { "Transform", "statement" } };
	Terminal["statement"] = Ruleset{ { "Transform", "argumentRequiring0" }, { "Transform", "argumentRequiring1" } };
	Terminal["controlStatement"] = Ruleset{ { "Transform", "flowStatement" } };
	Terminal["flowStatement"] = Ruleset{ { "Transform", "whileStatement" }, { "Transform", "ifStatement" } };
	Terminal["ifStatement"] = Ruleset{ { "Expand", "conditionalExpression", "statements" } };
	Terminal["elseIfStatement"] = Ruleset{ { "Expand", "conditionalExpression", "statements" } };
	// Semi-terminals
	Terminal["whileStatement"] = Ruleset{ { "Expand", "conditionalExpression", "statements" } };
	// Terminals Zero-way
	Terminal["argumentRequiring0"] = Ruleset{ { "Expand", "null" } };
	// Termninals One-way
	Terminal["elseStatement"] = Ruleset{ { "Expand", "statements" } };
	Terminal["argumentRequiring1"] = Ruleset{ { "Expand", "expression" } }; // issue
	Terminal["expression"] = Ruleset{ { "Expand", "null" } }; // issue
	Terminal["conditionalExpression"] = Ruleset{ { "Expand", "null" } }; // issue
	return Terminal[type];
}

const std::size_t Node::numberOfChildren() const 
{ 
	return child_.size(); 
}

void Node::addChild(const Node &child) 
{ 
	child_.push_back(child); 
}

const Node *Node::child(const std::size_t index) const 
{ 
	return &child_[index]; 
}

Node *Node::child(const std::size_t index) 
{ 
	return &child_[index]; 
}

const unsigned Node::getLevel() const
{
	return level_;
}

const bool Node::willExpand() const
{
	return need_expand_;
}

const std::string &Node::getData() const 
{ 
	return data_; 
}

const std::string &Node::getType() const
{
	return type_;
}