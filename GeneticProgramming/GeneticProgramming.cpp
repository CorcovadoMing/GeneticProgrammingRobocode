#include "RandomRange.h"
#include "GeneticProgramming.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include <algorithm>
#include <cstdlib>

using namespace AmqpClient;

GeneticProgramming::GeneticProgramming(const int populaion_size, const double mutation_rate) : population_size_(populaion_size), mutation_rate_(mutation_rate)
{
	population_ = PopulationGroup(population_group_size_, Population(populaion_size, Chromosome(GPtrees_size_, Tree("statements", 0, 0))));

	for (std::size_t i = 0; i < population_group_size_; i += 1)
	{
		for (std::size_t j = 0; j < populaion_size; j += 1)
		{
			population_[i][j][0] = Tree("statements", 0, 0);
			population_[i][j][1] = Tree("statements", 0, 1);
			population_[i][j][2] = Tree("statements", 0, 2);
		}
	}


	offspring_ = population_;

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
	offspring_fitness_ = std::vector< std::vector<double> >(population_group_size_, std::vector<double>(populaion_size, 0));
	selected_ = std::vector< std::vector<std::size_t> >(population_group_size_, std::vector<std::size_t>(populaion_size, 0));
	evaluate_populations_();
}

void GeneticProgramming::showPopulationFitness()
{
	double s_min[3] = {0};
	double s_avg[3] = {0};
	double s_max[3] = {0};
	for (std::size_t i = 0; i < population_group_size_; i += 1)
	{
		double sum = 0;
		double min = 999;
		double max = -1;
		for (std::size_t j = 0; j < population_size_; j += 1)
		{
			if (fitness_[i][j] > max)
			{
				max = fitness_[i][j];
			}
			if (fitness_[i][j] < min)
			{
				min = fitness_[i][j];
			}
			sum += fitness_[i][j];
			std::cout << fitness_[i][j] << std::endl;
		}
		s_max[i] = max;
		s_min[i] = min;
		s_avg[i] = sum/population_size_;
	}
	std::cout << "[Min Report]" << s_min[0] << " " << s_min[1] << " " << s_min[2] << std::endl;
	std::cout << "[Max Report]" << s_max[0] << " " << s_max[1] << " " << s_max[2] << std::endl;
	std::cout << "[Avg Report]" << s_avg[0] << " " << s_avg[1] << " " << s_avg[2] << std::endl;
}

void GeneticProgramming::writeFirst()
{
	std::string n[3] = {"0", "1", "2"};
	for (std::size_t i = 0; i < population_group_size_; i += 1)
	{
		int worst_index = -1;
		double worst = 999;
		for (std::size_t j = 0; j < fitness_[i].size(); j += 1)
		{
			if (fitness_[i][j] < worst)
			{
				worst = fitness_[i][j];
				worst_index = j;
			}
			std::ofstream fout;
			std::string filename= "bak/first/" + n[i] + ".java";
			fout.open(filename);
			makeRobot(population_[i][worst_index], fout);
			fout.close();
		}
	}
}

void GeneticProgramming::writeFinal()
{
	std::string n[3] = {"0", "1", "2"};
	for (std::size_t i = 0; i < population_group_size_; i += 1)
	{
		int best_index = -1;
		double best = -1;
		for (std::size_t j = 0; j < fitness_[i].size(); j += 1)
		{
			if (fitness_[i][j] > best)
			{
				best = fitness_[i][j];
				best_index = j;
			}
			std::ofstream fout;
			std::string filename= "bak/final/" + n[i] + ".java";
			fout.open(filename);
			makeRobot(population_[i][best_index], fout);
			fout.close();
		}
	}
}

void GeneticProgramming::matingSelection()
{
	for (std::size_t i = 0; i < population_group_size_; i += 1)
	{
		for (std::size_t j = 0; j < selected_[i].size(); j += 1)
		{
			const std::size_t first = RandomRange::random<int>(0, population_size_ - 1);
			const std::size_t second = RandomRange::random<int>(0, population_size_ - 1);
			// pick maximum
			if (fitness_[i][first] > fitness_[i][second])
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
	// for each population
	for (std::size_t pgsz = 0; pgsz < population_group_size_; pgsz += 1)
	{
		//for each selected candidate parent index to get chromosome
		for (std::size_t candi = 0; candi < selected_[pgsz].size(); candi += 2)
		{
			Chromosome chrom_x = population_[pgsz][selected_[pgsz][candi + 0]];
			Chromosome chrom_y = population_[pgsz][selected_[pgsz][candi + 1]];

			//for each trees in 2 chromosome
			for (std::size_t gpt = 0; gpt < GPtrees_size_; gpt += 1)
			{
				//get tree token type as a set.
				std::vector<std::string> chrom_x_stats = chrom_x[gpt].getAllStatments();
				std::vector<std::string> chrom_y_stats = chrom_y[gpt].getAllStatments();

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

			offspring_[pgsz][candi+0] = chrom_x;
			offspring_[pgsz][candi+1] = chrom_y;
		}
	}
}

void GeneticProgramming::crossover(Tree &tx, Tree &ty, const std::string &type)
{

	Node *nx = tx.getRandNodeByType(type);
	Node *ny = ty.getRandNodeByType(type);

	std::swap(*nx, *ny);

	tx.updateLevelRecursively(tx.root(), 0);
	ty.updateLevelRecursively(ty.root(), 0);
}

void GeneticProgramming::mutation()
{
	for (auto population : offspring_)
	{
		for (auto chromosome : population)
		{
			if (RandomRange::random<double>(0, 1) < mutation_rate_)
			{
				// mutate the one of the four part in each individual
				mutation(chromosome[RandomRange::random<int>(0, chromosome.size() - 1)]);
			}
		}
	}
}

void GeneticProgramming::mutation(Tree &tx)
{
	std::vector<std::string> stats = tx.getAllStatments();
	const std::size_t stat_idx = RandomRange::random<int>(0, stats.size() - 1);
	Node* mu = tx.getRandNodeByType(stats[stat_idx]);
	Tree new_mu(mu->getType(), mu->getLevel(), tx.getGPno());
	std::swap(*new_mu.root(), *mu);
}

void GeneticProgramming::environmentSelection()
{
	/*
	for (std::size_t i = 0; i < population_group_size_; i += 1)
	{
		for (std::size_t j = 0; j < population_size_; j += 1)
		{
			// generational model
			population_[i][j] = offspring_[i][j];
		}
	}*/

	// steady state
	evaluate_offsprings_();
	for (std::size_t i = 0; i < population_group_size_; i += 1)
	{
		for (std::size_t times = 0; times < population_size_; times += 1)
		{
			// find worst in the population
			int worst_index = -1;
			double worst = 999;
			for (std::size_t j = 0; j < fitness_[i].size(); j += 1)
			{
				if (fitness_[i][j] < worst)
				{
					worst = fitness_[i][j];
					worst_index = j;
				}
			}

			// find best in the offspring
			int best_index = -1;
			double best = -1;
			for (std::size_t j = 0; j < offspring_fitness_[i].size(); j += 1)
			{
				if (offspring_fitness_[i][j] > best)
				{
					best = offspring_fitness_[i][j];
					best_index = j;
				}
			}

			// replace population with offspring
			if (best > worst)
			{
				// std::cout << best << " > " << worst << std::endl;
				population_[i][worst_index] = offspring_[i][best_index];
				fitness_[i][worst_index] = offspring_fitness_[i][best_index];
			}
			offspring_fitness_[i][best_index] = 0;
		}
	}
}

void GeneticProgramming::evaluate_populations_()
{
	for (std::size_t i = 0; i < population_group_size_; i += 1)
	{
		for (std::size_t j = 0; j < population_[i].size(); j += 1)
		{
			fitness_[i][j] = evaluate_(population_[i][j], i);
			// std::cout << fitness_[i][j] << std::endl;
			if (fitness_[i][j] > best_[i])
			{
				best_[i] = fitness_[i][j];
			}
		}
	}
}

void GeneticProgramming::evaluate_offsprings_()
{
	for (std::size_t i = 0; i < population_group_size_; i += 1)
	{
		for (std::size_t j = 0; j < offspring_[i].size(); j += 1)
		{
			offspring_fitness_[i][j] = evaluate_(offspring_[i][j], i);
			// std::cout << offspring_fitness_[i][j] << std::endl;
			if (offspring_fitness_[i][j] > best_[i])
			{
				best_[i] = offspring_fitness_[i][j];
			}
		}
	}
}

// AMQP communication

void send(const int type)
{
	Channel::ptr_t channel = Channel::Create(getenv("RABBITMQ_PORT_5672_TCP_ADDR"));
	BasicMessage::ptr_t msg_in = BasicMessage::Create();
	std::stringstream ss;
	ss << type;
	msg_in->Body(ss.str());
	channel->DeclareExchange("control", "fanout");
	channel->BasicPublish("control", "", msg_in);
}

const double receive()
{
	Channel::ptr_t channel = Channel::Create(getenv("RABBITMQ_PORT_5672_TCP_ADDR"));
	channel->DeclareQueue("robocode_gp_control");
	channel->DeclareExchange("gp", "fanout");
	channel->BindQueue("robocode_gp_control", "gp", "robocode");
	channel->BasicConsume("robocode_gp_control", "consumertag");
	BasicMessage::ptr_t msg_out = channel->BasicConsumeMessage("consumertag")->Message();
	return atof(msg_out->Body().c_str());
}

const double GeneticProgramming::evaluate_(Chromosome &chromosome, const int type)
{
	std::ofstream fout;
	fout.open("ControlEngine/robots/GP/GP.java");
	makeRobot(chromosome, fout);
	fout.close();
	send(type);
	return receive();
}


void GeneticProgramming::makeRobot(Chromosome &chromosome, std::ofstream &fout)
{
	fout << "package GP;" << std::endl;
	fout << "import robocode.*;" << std::endl;
	fout << "import java.awt.Color;" << std::endl;
	fout << "import java.util.Random;" << std::endl;

	fout << "public class GP extends AdvancedRobot" << std::endl;
	fout << "{" << std::endl;
	fout << "	Enemy target;" << std::endl;
	fout << "	final double PI = Math.PI;" << std::endl;
	fout << "	int direction = 1;" << std::endl;
	fout << "	Random r = new Random();" << std::endl;
	fout << "	double firePower;" << std::endl;

	fout << "	public void run() {" << std::endl;
	fout << "		target = new Enemy();" << std::endl;
	fout << "		target.distance = 100000;" << std::endl;
	fout << "		setColors(Color.black,Color.black,Color.black);" << std::endl;
	fout << "		setAdjustGunForRobotTurn(true);" << std::endl;
	fout << "		setAdjustRadarForGunTurn(true);" << std::endl;
	fout << "		turnRadarRightRadians(2*PI);" << std::endl;
	fout << "		while(true) {" << std::endl;
	fout << "			doMovement();" << std::endl;
	fout << "			doScanner();" << std::endl;
	fout << "			doGun();" << std::endl;
	fout << "			execute();" << std::endl;
	fout << "		}" << std::endl;
	fout << "	}" << std::endl;
	fout << "	void doFire() {" << std::endl;
	chromosome[0].parse(fout);
	fout << "	}" << std::endl;
	fout << std::endl;
	fout << "	void doMovement() {" << std::endl;
	chromosome[1].parse(fout);
	fout << "	}" << std::endl;
	fout << "	public void onHitWall(HitWallEvent e) {" << std::endl;
	chromosome[2].parse(fout);
	fout << "	}" << std::endl;
	fout << "	public void reverseDirection(double any) {" << std::endl;
	fout << "		direction = direction * -1;" << std::endl;
	fout << "	}" << std::endl;
	fout << std::endl;
	fout << "	void doScanner() {" << std::endl;
	fout << "		double radarOffset;" << std::endl;
	fout << "		if (getTime() - target.ctime > 4) {" << std::endl;
	fout << "			radarOffset = 360;" << std::endl;
	fout << "		} else {" << std::endl;
	fout << "			radarOffset = getRadarHeadingRadians() - absbearing(getX(),getY(),target.x,target.y);" << std::endl;
	fout << "		}" << std::endl;
	fout << "		setTurnRadarLeftRadians(NormaliseBearing(radarOffset));" << std::endl;
	fout << "		setTurnGunLeftRadians(NormaliseBearing(radarOffset+90));" << std::endl;
	fout << "	}" << std::endl;
	fout << std::endl;
	fout << "	void doGun() {" << std::endl;
	fout << "		long time = getTime() + (int)(target.distance/(20-(3*firePower)));" << std::endl;
	fout << "		double gunOffset = getGunHeadingRadians() - absbearing(getX(),getY(),target.guessX(time),target.guessY(time));" << std::endl;
	fout << "		setTurnGunLeftRadians(NormaliseBearing(gunOffset));" << std::endl;
	fout << "		doFire();" << std::endl;
	fout << "	}" << std::endl;
	fout << std::endl;
	fout << "	double NormaliseBearing(double ang) {" << std::endl;
	fout << "		if (ang > PI)" << std::endl;
	fout << "			ang -= 2*PI;" << std::endl;
	fout << "		if (ang < -PI)" << std::endl;
	fout << "			ang += 2*PI;" << std::endl;
	fout << "		return ang;" << std::endl;
	fout << "	}" << std::endl;
	fout << std::endl;
	fout << "	double NormaliseHeading(double ang) {" << std::endl;
	fout << "		if (ang > 2*PI)" << std::endl;
	fout << "			ang -= 2*PI;" << std::endl;
	fout << "		if (ang < 0)" << std::endl;
	fout << "			ang += 2*PI;" << std::endl;
	fout << "		return ang;" << std::endl;
	fout << "	}" << std::endl;
	fout << std::endl;
	fout << "	public double getrange( double x1,double y1, double x2,double y2 )" << std::endl;
	fout << "	{" << std::endl;
	fout << "		double xo = x2-x1;" << std::endl;
	fout << "		double yo = y2-y1;" << std::endl;
	fout << "		double h = Math.sqrt( xo*xo + yo*yo );" << std::endl;
	fout << "		return h;" << std::endl;
	fout << "	}" << std::endl;
	fout << std::endl;
	fout << "	public double absbearing( double x1,double y1, double x2,double y2 )" << std::endl;
	fout << "	{" << std::endl;
	fout << "		double xo = x2-x1;" << std::endl;
	fout << "		double yo = y2-y1;" << std::endl;
	fout << "		double h = getrange( x1,y1, x2,y2 );" << std::endl;
	fout << "		if( xo > 0 && yo > 0 )" << std::endl;
	fout << "		{" << std::endl;
	fout << "			return Math.asin( xo / h );" << std::endl;
	fout << "		}" << std::endl;
	fout << "		if( xo > 0 && yo < 0 )" << std::endl;
	fout << "		{" << std::endl;
	fout << "			return Math.PI - Math.asin( xo / h );" << std::endl;
	fout << "		}" << std::endl;
	fout << "		if( xo < 0 && yo < 0 )" << std::endl;
	fout << "		{" << std::endl;
	fout << "			return Math.PI + Math.asin( -xo / h );" << std::endl;
	fout << "		}" << std::endl;
	fout << "		if( xo < 0 && yo > 0 )" << std::endl;
	fout << "		{" << std::endl;
	fout << "			return 2.0*Math.PI - Math.asin( -xo / h );" << std::endl;
	fout << "		}" << std::endl;
	fout << "		return 0;" << std::endl;
	fout << "	}" << std::endl;
	fout << std::endl;
	fout << "	public void onScannedRobot(ScannedRobotEvent e) {" << std::endl;
	fout << "		if ((e.getDistance() < target.distance)||(target.name == e.getName())) {" << std::endl;
	fout << "			double absbearing_rad = (getHeadingRadians()+e.getBearingRadians())%(2*PI);" << std::endl;
	fout << "			target.name = e.getName();" << std::endl;
	fout << "			target.x = getX()+Math.sin(absbearing_rad)*e.getDistance();" << std::endl;
	fout << "			target.y = getY()+Math.cos(absbearing_rad)*e.getDistance();" << std::endl;
	fout << "			target.bearing = e.getBearingRadians();" << std::endl;
	fout << "			target.head = e.getHeadingRadians();" << std::endl;
	fout << "			target.ctime = getTime();" << std::endl;
	fout << "			target.speed = e.getVelocity();" << std::endl;
	fout << "			target.distance = e.getDistance();" << std::endl;
	fout << "			target.energy = e.getEnergy();" << std::endl;
	fout << "		}" << std::endl;
	fout << "	}" << std::endl;
	fout << std::endl;
	fout << "	public void onRobotDeath(RobotDeathEvent e) {" << std::endl;
	fout << "		if (e.getName() == target.name)" << std::endl;
	fout << "			target.distance = 10000;" << std::endl;
	fout << "	}" << std::endl;
	fout << "}" << std::endl;
	fout << std::endl;
	fout << "class Enemy {" << std::endl;
	fout << "	String name;" << std::endl;
	fout << "	public double energy;" << std::endl;
	fout << "	public double bearing;" << std::endl;
	fout << "	public double head;" << std::endl;
	fout << "	public long ctime;" << std::endl;
	fout << "	public double speed;" << std::endl;
	fout << "	public double x,y;" << std::endl;
	fout << "	public double distance;" << std::endl;
	fout << "	public double guessX(long when)" << std::endl;
	fout << "	{" << std::endl;
	fout << "		long diff = when - ctime;" << std::endl;
	fout << "		return x+Math.sin(head)*speed*diff;" << std::endl;
	fout << "	}" << std::endl;
	fout << "	public double guessY(long when)" << std::endl;
	fout << "	{" << std::endl;
	fout << "		long diff = when - ctime;" << std::endl;
	fout << "		return y+Math.cos(head)*speed*diff;" << std::endl;
	fout << "	}" << std::endl;
	fout << "}" << std::endl;
}
