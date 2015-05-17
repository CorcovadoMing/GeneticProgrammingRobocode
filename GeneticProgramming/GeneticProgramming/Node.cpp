#include "Node.h"
#include "RandomRange.h"
#include <map>
#include <iostream>

Node::Node(const std::string &type, const int level) : type_(type), level_(level), data_("Never_space")
{
	const int Expected_Height = 5;
	// Growth
	if (level < Expected_Height)
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

Node::Node()
{

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
	Rule["argumentRequiring1"] = Ruleset{ { "Expand", "expression" } };
	Rule["expression"] = Ruleset{ { "Transform", "operator" }, { "Transform", "value" } };
	Rule["operator"] = Ruleset{ { "Transform", "plus" }, { "Transform", "minus" }, { "Transform", "multipal" }, { "Transform", "divide" } };
	Rule["value"] = Ruleset{ { "Transform", "constant" }, { "Transform", "variable" } };
	Rule["constant"] = Ruleset{ { "Expand", "null" } };
	Rule["variable"] = Ruleset{ { "Expand", "null" } };
	Rule["plus"] = Ruleset{ {"Expand", "value", "value"} };
	Rule["minus"] = Ruleset{ { "Expand", "value", "value" } };
	Rule["multipal"] = Ruleset{ { "Expand", "value", "value" } };
	Rule["divide"] = Ruleset{ { "Expand", "value", "value" } };
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
	Terminal["argumentRequiring1"] = Ruleset{ { "Expand", "expression" } };
	Terminal["expression"] = Ruleset{ { "Transform", "operator" }, { "Transform", "value" } };
	Terminal["operator"] = Ruleset{ { "Transform", "plus" }, { "Transform", "minus" }, { "Transform", "multipal" }, { "Transform", "divide" } };
	Terminal["value"] = Ruleset{ { "Transform", "constant" }, { "Transform", "variable" } };
	Terminal["constant"] = Ruleset{ { "Expand", "null" } };
	Terminal["variable"] = Ruleset{ { "Expand", "null" } };
	Terminal["plus"] = Ruleset{ { "Expand", "value", "value" } };
	Terminal["minus"] = Ruleset{ { "Expand", "value", "value" } };
	Terminal["multipal"] = Ruleset{ { "Expand", "value", "value" } };
	Terminal["divide"] = Ruleset{ { "Expand", "value", "value" } };
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

std::vector<Node> &Node::getChildrenNodes()
{
	return child_;
}

void Node::reset(const int level, const std::string &type, const std::string &data, const bool to_exp)
{
	type_ = type;
	data_ = data;
	level_ = level;
	need_expand_ = to_exp;
	child_.clear();
}