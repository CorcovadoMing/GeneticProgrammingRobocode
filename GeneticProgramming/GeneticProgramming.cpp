#include "RandomRange.h"
#include "GeneticProgramming.h"
#include <iostream>
#include <SimpleAmqpClient/SimpleAmqpClient.h>
using namespace AmqpClient;

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

// AMQP communication

void send()
{
	Channel::ptr_t channel = Channel::Create("localhost");
	BasicMessage::ptr_t msg_in = BasicMessage::Create();
	msg_in->Body("This is a small message.");
	channel->BasicPublish("control", "", msg_in);
}

void receive()
{
	Channel::ptr_t channel = Channel::Create("localhost");
	channel->DeclareQueue("robocode_gp_control");
	channel->BindQueue("robocode_gp_control", "gp", "robocode");
	channel->BasicConsume("robocode_gp_control", "consumertag");
	BasicMessage::ptr_t msg_out = channel->BasicConsumeMessage("consumertag")->Message();
	std::cout << "Message text: " << msg_out->Body() << std::endl;
}

const double GeneticProgramming::evaluate_(const Chromosome &chromosome)
{
	send();
	receive();
	return 0;
}