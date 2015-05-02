#include "Node.h"
#include "RandomRange.h"
#include <map>
#include <iostream>

Node::Node(const std::string &type, const int level) : type_(type), level_(level)
{
	// Growth
	if (level < 10)
	{
		Ruleset syntax = Node::GrowthRule(type);
		if (syntax.size())
		{
			const std::size_t index = RandomRange::random<int>(0, syntax.size() - 1);
			for (const std::string i : syntax[index])
			{
				child_.push_back(Node(i, level + 1));
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
			for (const std::string i : syntax[index])
			{
				child_.push_back(Node(i, level + 1));
			}
		}
	}
}

const Ruleset &Node::GrowthRule(const std::string &type)
{
	static std::map<std::string, Ruleset> Rule;

	Rule["statements"] = Ruleset{ { "statement", "statements", "controlStatement" }, { "statement" } };
	Rule["statement"] = Ruleset{ { "controlStatement" }, { "argumentRequiring0" }, { "argumentRequiring1" }, { "argumentRequiring2" } };
	Rule["controlStatement"] = Ruleset{ { "flowStatement" } };

	Rule["flowStatement"] = Ruleset{ { "whileStatement" }, { "ifStatement" } };
	Rule["ifStatement"] = Ruleset{ { "ifStatement", "elseIfStatement" }, { "conditionalExpression", "statements" } };
	Rule["elseIfStatement"] = Ruleset{ { "elseIfStatement", "elseIfStatement" }, { "elseIfStatement", "elseStatement" }, { "conditionalExpression", "statements" } };
	
	// Semi-terminals
	Rule["whileStatement"] = Ruleset{ { "conditionalExpression", "statements" } };

	// Terminals Zero-way
	Rule["argumentRequiring0"] = Ruleset{ {} };

	// Termninals One-way
	Rule["elseStatement"] = Ruleset{ { "statements" } };

	Rule["argumentRequiring1"] = Ruleset{ { "expression" } }; // issue
	Rule["expression"] = Ruleset{ {} }; // issue
	
	return Rule[type];
}

const Ruleset &Node::TerminalRule(const std::string &type)
{
	static std::map<std::string, Ruleset> Terminal;

	Terminal["statements"] = Ruleset{ { "statement" } };
	Terminal["statement"] = Ruleset{ { "argumentRequiring0" }, { "argumentRequiring1" }, { "argumentRequiring2" } };
	Terminal["controlStatement"] = Ruleset{ { "flowStatement" } };

	Terminal["flowStatement"] = Ruleset{ { "whileStatement" }, { "ifStatement" } };
	Terminal["ifStatement"] = Ruleset{ { "conditionalExpression", "statements" } };
	Terminal["elseIfStatement"] = Ruleset{ { "conditionalExpression", "statements" } };

	// Semi-terminals
	Terminal["whileStatement"] = Ruleset{ { "conditionalExpression", "statements" } };

	// Terminals Zero-way
	Terminal["argumentRequiring0"] = Ruleset{ {} };

	// Termninals One-way
	Terminal["elseStatement"] = Ruleset{ { "statements" } };

	Terminal["argumentRequiring1"] = Ruleset{ { "expression" } }; // issue
	Terminal["expression"] = Ruleset{ {} }; // issue

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

const int Node::getLevel() const
{
	return level_;
}

const std::string &Node::getData() const 
{ 
	return data_; 
}

const std::string &Node::getType() const
{
	return type_;
}