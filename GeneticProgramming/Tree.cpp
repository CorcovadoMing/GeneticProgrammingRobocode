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

void Tree::parse(std::ostream &fout)
{
	parse(fout, &root_);
}

void Tree::parse(std::ostream &fout, Node *node, const bool withNewLine, int indent)
{
	if (node->willExpand())
	{
		for (std::size_t i = 0; i < indent; i += 1)
		{
			fout << " ";
		}

		if (node->getType() == "whileStatement" && node->numberOfChildren() == 2)
		{
			fout << "while (";
			parse(fout, node->child(0), false, 1);
			fout << " ) {" << std::endl;
			indent += 4;
			parse(fout, node->child(1), true, indent);
			indent -= 4;

			for (std::size_t i = 0; i < indent; i += 1)
			{
				fout << " ";
			}

			fout << "}" << std::endl;
		}
		else if (node->getType() == "ifStatement" && node->numberOfChildren() == 2)
		{
			fout << "if (";
			parse(fout, node->child(0), false, 1);
			fout << " ) {" << std::endl;
			indent += 4;
			parse(fout, node->child(1), true, indent);
			indent -= 4;

			for (std::size_t i = 0; i < indent; i += 1)
			{
				fout << " ";
			}

			fout << "}" << std::endl;
		}
		else if (node->getType() == "elseIfStatement" && node->numberOfChildren() == 2)
		{
			fout << "else if (";
			parse(fout, node->child(0), false, 1);
			fout << " ) {" << std::endl;
			indent += 4;
			parse(fout, node->child(1), true, indent);
			indent -= 4;

			for (std::size_t i = 0; i < indent; i += 1)
			{
				fout << " ";
			}

			fout << "}" << std::endl;
		}
		else if (node->getType() == "elseStatement" && node->numberOfChildren() == 1)
		{
			fout << "else {" << std::endl;
			indent += 4;
			parse(fout, node->child(0), true, indent);
			indent -= 4;

			for (std::size_t i = 0; i < indent; i += 1)
			{
				fout << " ";
			}

			fout << "}" << std::endl;
		}
		else if (node->getType() == "argumentRequiring1" && node->numberOfChildren() == 1)
		{
			if (node->getData() == "null")
			{
				node->setData(Tree::randomArgumentRequiring1(GP_no_));
			}
			fout << node->getData() << "(";
			parse(fout, node->child(0), false, 1);
			fout << " );" << std::endl;
		}
		else if (node->getType() == "expression")
		{
			fout << "(";

			for (std::size_t i = 0; i < node->numberOfChildren(); i += 1)
			{
				parse(fout, node->child(i), false, 1);
			}

			fout << " )";
		}
		else
		{
			if (withNewLine)
			{
				if (node->getType() == "constant")
				{
					fout << node->getData() << ";" << std::endl;
				}
				else if (node->getType() == "variable")
				{
					if (node->getData() == "null")
					{
						node->setData(Tree::randomVariable(GP_no_));
					}
					fout << node->getData() << ";" << std::endl;
				}
				else if (node->getType() == "argumentRequiring0")
				{
					if (node->getData() == "null")
					{
						node->setData(Tree::randomArgumentRequiring0(GP_no_));
					}
					fout << node->getData() << ";" << std::endl;
				}
				else
				{
					fout << node->getType() << ";" << std::endl;
				}
			}
			else
			{
				if (node->getType() == "constant")
				{
					fout << node->getData();
				}
				else if (node->getType() == "variable")
				{
					if (node->getData() == "null")
					{
						node->setData(Tree::randomVariable(GP_no_));
					}
					fout << node->getData();
				}
				else if (node->getType() == "argumentRequiring0")
				{
					if (node->getData() == "null")
					{
						node->setData(Tree::randomArgumentRequiring0(GP_no_));
					}
					fout << node->getData();
				}
				else
				{
					fout << node->getType();
				}
			}

			for (std::size_t i = 0; i < node->numberOfChildren(); i += 1)
			{
				parse(fout, node->child(i), withNewLine, indent);
			}
		}
	}
	else
	{
		for (std::size_t i = 0; i < node->numberOfChildren(); i += 1)
		{
			parse(fout, node->child(i), withNewLine, indent);
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

	table[1].push_back("target.x");
	table[1].push_back("target.y");
	table[1].push_back("target.bearing");
	table[1].push_back("target.head");
	table[1].push_back("target.speed");
	table[1].push_back("target.distance");
	table[1].push_back("target.energy");
	table[1].push_back("direction");

	table[2].push_back("target.x");
	table[2].push_back("target.y");
	table[2].push_back("target.bearing");
	table[2].push_back("target.head");
	table[2].push_back("target.speed");
	table[2].push_back("target.distance");
	table[2].push_back("target.energy");
	table[2].push_back("direction");

	// All the type should be the same, *for now*
	const std::size_t index = RandomRange::random<int>(0, table[type].size() - 1);
	return table[type][index];
}
	
const std::string &Tree::randomArgumentRequiring0(const int type)
{
	static Table table(3);
	table[0].push_back("//nothing");

	table[1].push_back("//nothing");

	table[2].push_back("//nothing");

	const std::size_t index = RandomRange::random<int>(0, table[type].size() - 1);
	return table[type][index];
}

const std::string &Tree::randomArgumentRequiring1(const int type)
{
	static Table table(3);
	table[0].push_back("fire");

	table[1].push_back("setAhead");
	table[1].push_back("setTurnRightRadians");

	table[2].push_back("setAhead");
	table[2].push_back("setTurnRightRadians");

	const std::size_t index = RandomRange::random<int>(0, table[type].size() - 1);
	return table[type][index];
}

const std::vector<std::string> Tree::getAllStatments() const
{
	std::set<std::string> set;
	getTypeRecursively(set, root());
	std::vector<std::string> ret(set.begin(), set.end());
	return ret;
}

const std::vector<Node *> Tree::getNodesByType(const std::string &type)
{
	std::vector<Node *> set;
	getNodesByTypeRecursively(set, root(), type);
	return set;
}

void Tree::getTypeRecursively(std::set<std::string> &set, const Node *node) const
{
	for (std::size_t i = 0; i < node->numberOfChildren(); i += 1)
	{
		getTypeRecursively(set, node->child(i));
	}

	set.insert(node->getType());
}

Node *Tree::getRandNodeByType(const std::string &type)
{
	std::vector<Node *> set;
	getNodesByTypeRecursively(set, root(), type);
	return set[RandomRange::random<int>(0, set.size() - 1)];
}

void Tree::getNodesByTypeRecursively(std::vector<Node *> &set, Node *node, const std::string &type) const
{
	for (std::size_t i = 0; i < node->numberOfChildren(); i += 1)
	{
		getNodesByTypeRecursively(set, node->child(i), type);
	}

	if (node->getType() == type)
	{
		set.push_back(node);
	}
}

void Tree::updateLevelRecursively(Node *node, const int level)
{
	node->setLevel(level);

	for (std::size_t i = 0; i < node->numberOfChildren(); i += 1)
	{
		updateLevelRecursively(node->child(i), level + 1);
	}
} 
