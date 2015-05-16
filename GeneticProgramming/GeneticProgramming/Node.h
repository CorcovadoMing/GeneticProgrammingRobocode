#pragma once
#include <string>
#include <vector>
#include <map>

typedef std::vector<std::string> Rule;
typedef std::vector< std::vector<std::string> > Ruleset;

class Node
{
public:
	Node(const std::string &, const int);
	Node();

	const std::size_t numberOfChildren() const;
	void addChild(const Node &);
	const Node *child(const std::size_t) const;
	Node *child(const std::size_t);

	const unsigned getLevel() const;
	const bool willExpand() const;
	const std::string &getData() const;
	const std::string &getType() const;
	std::vector<Node> &getChildrenNodes();

	void reset(const int, const std::string &, const std::string &, const bool);

private:
	unsigned level_;
	bool need_expand_;
	std::string data_;
	std::string type_;
	std::vector<Node> child_;

	static const Ruleset &GrowthRule(const std::string &);
	static const Ruleset &TerminalRule(const std::string &);
};
