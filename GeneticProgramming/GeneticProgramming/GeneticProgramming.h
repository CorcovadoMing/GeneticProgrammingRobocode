#pragma once
class GeneticProgramming
{
public:
	GeneticProgramming();
	void initialize();
	void matingSelection();
	void crossover();
	void mutation();
	void environmentSelection();
private:
	const double evaluate_();
	const double mutation_rate_;
};

