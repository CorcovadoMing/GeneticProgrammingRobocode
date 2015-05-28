#include "Tree.h"
#include "RandomRange.h"
#include <iostream>
#include <fstream>
#include <algorithm>


Tree::Tree(const std::string &type, const int level, const int GP_no) : root_(type, level), GP_no_(GP_no)
{
}

void Tree::exportTo(const char *filename) const
{
	std::ofstream fout;
	fout.open(filename);
	fout << getGPno() << std::endl;
	fprint(fout, this->root());
	fout.close();
}

void Tree::fprint(std::ofstream &fout, const Node *node) const
{
	fout << node->getLevel() << " "
	     << node->getType() << " "
	     << node->getData() << " "
	     << node->numberOfChildren() << " "
	     << node->willExpand() << std::endl;

	for (std::size_t i = 0; i < node->numberOfChildren(); i += 1)
	{
		fprint(fout, node->child(i));
	}
}

void Tree::importFrom(const char *filename)
{
	std::ifstream fin;
	fin.open(filename);
	int gpn;
	fin >> gpn;
	setGPno(gpn);
	fscan(fin, root());
	fin.close();
}

void Tree::fscan(std::ifstream &fin, Node *node)
{
	int lv, nchild, toexp;
	std::string type, data;
	fin >> lv >> type >> data >> nchild >> toexp;
	node->reset(lv, type, data, (toexp > 0));

	for (std::size_t i = 0; i < nchild; i += 1)
	{
		Node x;
		node->getChildrenNodes().push_back(x);
		fscan(fin, node->child(i));
	}
}

void Tree::print() const
{
	std::cout << "[Root " << root_.getLevel() << "] " << root_.getType() << " " << root_.willExpand() << std::endl;

	for (std::size_t i = 0; i < root_.numberOfChildren(); i += 1)
	{
		print(root_.child(i));
	}
}

void Tree::print(const Node *node) const
{
	const std::string space = "  ";

	for (std::size_t i = 0; i < node->getLevel(); i += 1)
	{
		std::cout << space;
	}

	std::cout << "[Node " << node->getLevel() << "] " << node->getType() << " " << node->willExpand() << std::endl;

	for (std::size_t i = 0; i < node->numberOfChildren(); i += 1)
	{
		print(node->child(i));
	}
}

void Tree::parse()
{
	parse(&root_);
}

void Tree::parse(Node *node, const bool withNewLine, int indent)
{
	if (node->willExpand())
	{
		for (std::size_t i = 0; i < indent; i += 1)
		{
			std::cout << " ";
		}

		if (node->getType() == "whileStatement" && node->numberOfChildren() == 2)
		{
			std::cout << "while (";
			parse(node->child(0), false, 1);
			std::cout << " ) {" << std::endl;
			indent += 4;
			parse(node->child(1), true, indent);
			indent -= 4;

			for (std::size_t i = 0; i < indent; i += 1)
			{
				std::cout << " ";
			}

			std::cout << "}" << std::endl;
		}
		else if (node->getType() == "ifStatement" && node->numberOfChildren() == 2)
		{
			std::cout << "if (";
			parse(node->child(0), false, 1);
			std::cout << " ) {" << std::endl;
			indent += 4;
			parse(node->child(1), true, indent);
			indent -= 4;

			for (std::size_t i = 0; i < indent; i += 1)
			{
				std::cout << " ";
			}

			std::cout << "}" << std::endl;
		}
		else if (node->getType() == "elseIfStatement" && node->numberOfChildren() == 2)
		{
			std::cout << "else if (";
			parse(node->child(0), false, 1);
			std::cout << " ) {" << std::endl;
			indent += 4;
			parse(node->child(1), true, indent);
			indent -= 4;

			for (std::size_t i = 0; i < indent; i += 1)
			{
				std::cout << " ";
			}

			std::cout << "}" << std::endl;
		}
		else if (node->getType() == "elseStatement" && node->numberOfChildren() == 1)
		{
			std::cout << "else {" << std::endl;
			indent += 4;
			parse(node->child(0), true, indent);
			indent -= 4;

			for (std::size_t i = 0; i < indent; i += 1)
			{
				std::cout << " ";
			}

			std::cout << "}" << std::endl;
		}
		else if (node->getType() == "argumentRequiring1" && node->numberOfChildren() == 1)
		{
			node->setData(Tree::randomArgumentRequiring1(GP_no_));
			std::cout << node->getData() << "(";
			parse(node->child(0), false, 1);
			std::cout << " );" << std::endl;
		}
		else if (node->getType() == "expression")
		{
			std::cout << "(";

			for (std::size_t i = 0; i < node->numberOfChildren(); i += 1)
			{
				parse(node->child(i), false, 1);
			}

			std::cout << " )";
		}
		else
		{
			if (withNewLine)
			{
				if (node->getType() == "constant")
				{
					std::cout << node->getData() << ";" << std::endl;
				}
				else if (node->getType() == "variable")
				{
					node->setData(Tree::randomVariable(GP_no_));
					std::cout << node->getData() << ";" << std::endl;
				}
				else if (node->getType() == "argumentRequiring0")
				{
					node->setData(Tree::randomArgumentRequiring0(GP_no_));
					std::cout << node->getData() << ";" << std::endl;
				}
				else
				{
					std::cout << node->getType() << ";" << std::endl;
				}
			}
			else
			{
				if (node->getType() == "constant")
				{
					std::cout << node->getData();
				}
				else if (node->getType() == "variable")
				{
					node->setData(Tree::randomVariable(GP_no_));
					std::cout << node->getData();
				}
				else if (node->getType() == "argumentRequiring0")
				{
					node->setData(Tree::randomArgumentRequiring0(GP_no_));
					std::cout << node->getData();
				}
				else
				{
					std::cout << node->getType();
				}
			}

			for (std::size_t i = 0; i < node->numberOfChildren(); i += 1)
			{
				parse(node->child(i), withNewLine, indent);
			}
		}
	}
	else
	{
		for (std::size_t i = 0; i < node->numberOfChildren(); i += 1)
		{
			parse(node->child(i), withNewLine, indent);
		}
	}
}

const std::string &Tree::randomVariable(const int type)
{
	static Table table(3);
	table[0].push_back("target.x");
	table[0].push_back("target.y");
	table[0].push_back("target.bearing");
	table[0].push_back("target.head");
	table[0].push_back("target.speed");
	table[0].push_back("target.distance");
	table[0].push_back("target.energy");

	const std::size_t index = RandomRange::random<int>(0, table[type].size() - 1);
	return table[type][index];
}

const std::string &Tree::randomArgumentRequiring0(const int type)
{
	static Table table(3);
	table[0].push_back("//nothing");

	const std::size_t index = RandomRange::random<int>(0, table[type].size() - 1);
	return table[type][index];
}

const std::string &Tree::randomArgumentRequiring1(const int type)
{
	static Table table(3);
	table[0].push_back("fire");

	const std::size_t index = RandomRange::random<int>(0, table[type].size() - 1);
	return table[type][index];
}

const std::set<std::string> Tree::getAllStatments() const
{
	std::set<std::string> set;
	getTypeResursively(set, root());
	return set;
}

void Tree::getTypeResursively(std::set<std::string> &set, const Node *node) const
{
	for (std::size_t i = 0; i < node->numberOfChildren() && !node->willExpand(); i += 1)
	{
		getTypeResursively(set, node->child(i));
	}

	set.insert(node->getType());
}
