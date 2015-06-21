#include "GeneticProgramming.h"
#include <iostream>
#include <fstream>

int main()
{
	std::cout << "[GP] initializeing...";
	GeneticProgramming gp(10, 0.5); // population_size, mutation_rate
	std::cout << "Done" << std::endl;

	std::cout << "[GP] Evolving..." << std::endl;
	const int LOOPTIMES = 10;
	int looptimes = LOOPTIMES;
	while(looptimes--)
	{
		std::cout << "[GP] Generation " << LOOPTIMES-looptimes << std::endl;
		gp.matingSelection();
		std::cout << "[GP] Crossover..." << std::endl;
		gp.crossover();
		std::cout << "[GP] Mutation..." << std::endl;
		gp.mutation();
		std::cout << "[GP] EnvironmentSelection..." << std::endl;
		gp.environmentSelection();
	}
	std::cout << "[GP] Process terminate" << std::endl;
	return 0;
}
