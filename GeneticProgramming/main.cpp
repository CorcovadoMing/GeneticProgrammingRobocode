#include "GeneticProgramming.h"
#include <iostream>
#include <fstream>

int main()
{
	std::cout << "[GP] initializeing...";
	GeneticProgramming gp(10, 0.5); // population_size, mutation_rate
	std::cout << "Done" << std::endl;

	std::cout << "[GP] Evolving..." << std::endl;
	const int LOOPTIMES = 100;
	int looptimes = LOOPTIMES;
	while(looptimes--)
	{
		std::cout << "[GP] Generation " << LOOPTIMES-looptimes << std::endl;
		gp.matingSelection();
		gp.crossover();
		gp.mutation();
		gp.environmentSelection();
		std::cout << "[Best Report] " << gp.getBest(0) << " " << gp.getBest(1) << " " << gp.getBest(2) << std::endl;
	}
	std::cout << "[GP] Process terminate" << std::endl;
	return 0;
}
