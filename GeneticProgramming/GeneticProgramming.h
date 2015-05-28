#pragma once
#include "Tree.h"
#include <vector>

class GeneticProgramming
{
	typedef std::vector<Tree> Chromosome;
	typedef std::vector<Chromosome> Population;
	typedef std::vector<Population> PopulationGroup;
public:
	GeneticProgramming(const int, const double);
	void matingSelection();
	void crossover();
	void crossover(Tree &, Tree &, const std::string &);
	void mutation();
	void mutation(Tree &);
	void environmentSelection();
private:
	//void evaluate_populations_();
	//const double evaluate_(const Chromosome &);

	PopulationGroup population_;
	std::vector< std::vector<double> > fitness_;
	std::vector< std::vector<std::size_t> > selected_;
	const double mutation_rate_;
	const std::size_t population_size_;

	const std::size_t population_group_size_ = 3;
	const std::size_t GPtrees_size_ = 3;
};

