#include "GeneticProgramming.h"
#include <iostream>
#include <fstream>

int main()
{
	std::cout << "[GP] initializeing...";
	GeneticProgramming gp(10, 0.4); // population_size, mutation_rate
	std::cout << "Done" << std::endl;

	std::cout << "[GP] Evolving..." << std::endl;
	gp.matingSelection();
	gp.crossover();
	gp.mutation();
	gp.environmentSelection();

	std::cout << "[GP] Process terminate" << std::endl;
	return 0;
}
