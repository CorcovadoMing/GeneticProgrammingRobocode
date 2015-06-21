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

	const double getBest(const int index) const { return best_[index]; }

private:
	void evaluate_populations_();
	void evaluate_offsprings_();
	const double evaluate_(Chromosome &, const int type);
	void makeRobot(Chromosome &, std::ofstream &);

	PopulationGroup population_;
	PopulationGroup offspring_;

	std::vector< std::vector<double> > fitness_, offspring_fitness_;
	std::vector< std::vector<std::size_t> > selected_;

	double best_[3] = {0};
	const double mutation_rate_;
	const std::size_t population_size_;
	const std::size_t population_group_size_ = 3;
	const std::size_t GPtrees_size_ = 3;
};

