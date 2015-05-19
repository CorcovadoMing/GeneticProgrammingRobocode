#include "RandomRange.h"
#include "GeneticProgramming.h"
#include <iostream>

GeneticProgramming::GeneticProgramming(const int populaion_size, const double mutation_rate) : population_size_(populaion_size), mutation_rate_(mutation_rate)
{
	population_ = PopulationGroup(population_group_size_, Population(populaion_size, Chromosome(GPtrees_size_, Tree("statements", 0, 0))));

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

	fitness_ = std::vector< std::vector<double> >(population_group_size_, std::vector<double>(populaion_size, 0));
	selected_ = std::vector< std::vector<std::size_t> >(population_group_size_, std::vector<std::size_t>(populaion_size / 2, 0));
}

void GeneticProgramming::matingSelection()
{
	evaluate_populations_();
	for (std::size_t i = 0; i < population_group_size_; i += 1)
	{
		for (std::size_t j = 0; j < selected_[i].size(); j += 1)
		{
			const std::size_t first = RandomRange::random<int>(0, population_size_ - 1);
			const std::size_t second = RandomRange::random<int>(0, population_size_ - 1);
			if (fitness_[i][first] < fitness_[i][second])
			{
				selected_[i][j] = first;
			}
			else
			{
				selected_[i][j] = second;
			}
		}
	}
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

void GeneticProgramming::evaluate_populations_()
{
	for (std::size_t i = 0; i < population_group_size_; i += 1)
	{
		for (std::size_t j = 0; j < population_[i].size(); j += 1)
		{
			fitness_[i][j] = evaluate_(population_[i][j]);
		}
	}
}

const double GeneticProgramming::evaluate_(const Chromosome &chromosome)
{
	return 0;
}