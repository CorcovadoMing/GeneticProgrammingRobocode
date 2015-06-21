#include "GeneticProgramming.h"
#include <iostream>
#include <fstream>

int main()
{
	std::cout << "[GP] initializeing..." << std::endl;
	GeneticProgramming gp(10, 0.5); // population_size, mutation_rate
	std::cout << "Done" << std::endl;
	gp.writeFirst();
	std::cout << "[GP] Evolving..." << std::endl;
	const int LOOPTIMES = 50;
	int looptimes = LOOPTIMES;
	
	std::cout << "[GP] Generation 0" << std::endl;
	gp.showPopulationFitness();
	std::cout << "[Best Report] " << gp.getBest(0) << " " << gp.getBest(1) << " " << gp.getBest(2) << std::endl;

	while(looptimes--)
	{
		std::cout << "[GP] Generation " << LOOPTIMES-looptimes << std::endl;
		gp.matingSelection();
		gp.crossover();
		gp.mutation();
		gp.environmentSelection();
		gp.showPopulationFitness();
		std::cout << "[Best Report] " << gp.getBest(0) << " " << gp.getBest(1) << " " << gp.getBest(2) << std::endl;
	}
	gp.writeFinal();
	std::cout << "[GP] Process terminate" << std::endl;
	return 0;
}
