#include "GeneticProgramming.h"
#include <iostream>
#include <fstream>

int main()
{
	
	Tree tree("statements", 0, 0);
	//tree.exportTo("iotest.txt");
	//tree.importFrom("iotest.txt");
	
	// std::ofstream fout;
	// fout.open("test.txt");
	// //tree.parse(std::cout);
	// tree.parse(fout);
	// fout.close();
	
	/*
	std::cout << "Original: " << std::endl;
	tree.parse();
    
    tree.exportTo("1.txt");

	Tree another_tree("flowStatement", 0);
	
	std::cout << std::endl << "Another Tree:" << std::endl;
	another_tree.parse();

	another_tree.importFrom("1.txt");
	std::cout << std::endl << "After import:" << std::endl;
	another_tree.parse();
	//std::swap(*another_tree_root->child(0), *root->child(0));
	std::cout << std::endl;
	*/

	GeneticProgramming gp(10, 0.4); // population_size, mutation_rate
	gp.matingSelection();
	gp.crossover();
	//gp.mutation();
	//gp.environmentSelection();
	return 0;
}