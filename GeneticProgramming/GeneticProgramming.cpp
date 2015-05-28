#include "RandomRange.h"
#include "GeneticProgramming.h"
#include <iostream>
#include <algorithm>

//#include <SimpleAmqpClient/SimpleAmqpClient.h>
//using namespace AmqpClient;

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
	//need even size for fake data
	selected_ = std::vector< std::vector<std::size_t> >(population_group_size_, std::vector<std::size_t>(populaion_size / 2 + 1, 0));
}

void GeneticProgramming::matingSelection()
{
//	evaluate_populations_();
	for (std::size_t i = 0; i < population_group_size_; i += 1)
	{
		for (std::size_t j = 0; j < selected_[i].size(); j += 2)
		{
			const std::size_t first = RandomRange::random<int>(0, population_size_ - 1);
			const std::size_t second = RandomRange::random<int>(0, population_size_ - 1);
            //fake selected
            selected_[i][j] = first;
			selected_[i][j+1] = second;
		}
	}
}

void GeneticProgramming::crossover()
{
	// for each population
	for (std::size_t pgsz = 0; pgsz < population_group_size_; pgsz += 1)
	{
		//for each selected candidate parent index to get chromosome
		for (std::size_t candi = 0; candi < selected_[pgsz].size(); candi += 2)
		{
			Chromosome &chrom_x = population_[pgsz][selected_[pgsz][candi + 0]];
			Chromosome &chrom_y = population_[pgsz][selected_[pgsz][candi + 1]];

			//for each trees in 2 chromosome
			for (std::size_t gpt = 0; gpt < GPtrees_size_; gpt += 1)
			{
				//get tree token type as a set.
				std::set<std::string> chrom_x_stats = chrom_x[gpt].getAllStatments();
				std::set<std::string> chrom_y_stats = chrom_y[gpt].getAllStatments();

				//find intersection. Refer from http://www.cplusplus.com/reference/algorithm/set_intersection/
				std::vector<std::string> intersection(std::max(chrom_x_stats.size(), chrom_y_stats.size()));

				auto it = std::set_intersection(chrom_x_stats.begin(), chrom_x_stats.end(),
				                                chrom_y_stats.begin(), chrom_y_stats.end(),
				                                intersection.begin());

				intersection.resize(it - intersection.begin());

				//random pick one of intersection index
				const std::size_t inter_stat_idx = RandomRange::random<int>(0, intersection.size() - 1);

				//cross over 2 tree that has same program logic block
				crossover(chrom_x[gpt], chrom_y[gpt], intersection[inter_stat_idx]);
			}
		}
	}
}

void GeneticProgramming::crossover(Tree &tx, Tree &ty, const std::string &type)
{
	std::swap(*tx.getRandNodeByType(type), *ty.getRandNodeByType(type));
}

void GeneticProgramming::mutation()
{

}

void GeneticProgramming::environmentSelection()
{

}

//void GeneticProgramming::evaluate_populations_()
//{
//	for (std::size_t i = 0; i < population_group_size_; i += 1)
//	{
//		for (std::size_t j = 0; j < population_[i].size(); j += 1)
//		{
//			fitness_[i][j] = evaluate_(population_[i][j]);
//		}
//	}
//}

//void send()
//{
//	Channel::ptr_t channel = Channel::Create("localhost");
//	BasicMessage::ptr_t msg_in = BasicMessage::Create();
//	msg_in->Body("This is a small message.");
//	channel->BasicPublish("control", "", msg_in);
//}

//void receive()
//{
//	Channel::ptr_t channel = Channel::Create("localhost");
//	channel->DeclareQueue("robocode_gp_control");
//	channel->BindQueue("robocode_gp_control", "gp", "robocode");
//	channel->BasicConsume("robocode_gp_control", "consumertag");
//	BasicMessage::ptr_t msg_out = channel->BasicConsumeMessage("consumertag")->Message();
//	std::cout << "Message text: " << msg_out->Body() << std::endl;
//}

//const double GeneticProgramming::evaluate_(const Chromosome &chromosome)
//{
//	send();
//	receive();
//	return 0;
//}