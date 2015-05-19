#include "GeneticProgramming.h"

GeneticProgramming::GeneticProgramming(const int populaion_size, const double mutation_rate) : population_size_(populaion_size), mutation_rate_(mutation_rate)
{
	const int population_group_size = 3;
	const int GPtrees_size = 3;

	population_ = PopulationGroup(population_group_size, Population(populaion_size, Chromosome(GPtrees_size, Tree("statements", 0, 0))));

	for (auto population : population_)
	{
		for (auto chromosome : population)
		{
			for (std::size_t i = 0; i < chromosome.size(); i += 1)
			{
				chromosome[i].setGPno(i);
			}
		}
	}
}

void GeneticProgramming::matingSelection()
{

}

void GeneticProgramming::crossover()
{

}

void GeneticProgramming::mutation()
{

}

void GeneticProgramming::environmentSelection()
{

}

const double GeneticProgramming::evaluate_()
{
	return 0;
}