#include "GeneticProgramming.h"
#include <iostream>
#include <fstream>

int main()
{
	GeneticProgramming gp(10, 0.4); // population_size, mutation_rate
	gp.matingSelection();
	gp.crossover();
	gp.mutation();
	gp.environmentSelection();
	return 0;
}
