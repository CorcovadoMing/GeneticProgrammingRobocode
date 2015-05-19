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
	void mutation();
	void environmentSelection();
private:
	PopulationGroup population_;
	std::vector<std::size_t> selected_;
	const double evaluate_();
	const double mutation_rate_;
	const int population_size_;
};

