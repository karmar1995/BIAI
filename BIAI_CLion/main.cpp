#include <iostream>
#include <cstdlib>
#include <time.h>
#include "IGeneticOperator.h"
#include "GraphManager.h"
#include <memory>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <fstream>
#include <ostream>
#include <string>

void help() {
	std::cout << "Proper program usage: TravellingSalesman <-i File_Path> <-> [-o File_Path] [-t]\
\n\t -i - Input file location\
\n\t -o - Output file location for generation of sample data\
\n\t -n - Number of iterations\
\n\t -c - Number of chromosomes\
\n\t -t - Writes execution time at end of output file\n";
	system("pause");
}

std::vector<Chromosome> Operate(std::string input,int nuberOfChromosomes,int numberOfCycles) {
	srand(time(NULL));
	std::shared_ptr<ICrossover> crossover(new EdgeCrossover);
	std::shared_ptr<IMutation> mutator(new ScrambleMutation);
	GraphFileParser ts(input);
	GraphMap map = ts.ParseFile();
	GraphManager manager(map);

	std::vector<Chromosome> Chromosomes;
	for (int i = 0; i < nuberOfChromosomes *2; i++) {
		Chromosomes.push_back(Chromosome(map.size()));
	}

	for (Chromosome& c : Chromosomes) {
		c.setFitness(manager.getCostForTrace(c.getGenes()));
	}

	std::sort(Chromosomes.begin(), Chromosomes.end(), Better());
	Chromosomes.erase(Chromosomes.begin() + nuberOfChromosomes, Chromosomes.end());

	for (int j = 0; j < numberOfCycles; j++) {
		for (int i = 0; i < Chromosomes.size(); i++)
		{
			if (rand() % 50 == 0)
				Chromosomes[i] = mutator->Mutate(Chromosomes[i]);
			ChromosomePair parents = std::make_pair(Chromosomes[i], Chromosomes[i + 1]);
			ChromosomePair offsprings = crossover->Crossover(parents);
			Chromosomes[i] = offsprings.first;
			Chromosomes[i].setFitness(manager.getCostForTrace(Chromosomes[i].getGenes()));
			i++;
			Chromosomes[i] = offsprings.second;
			Chromosomes[i].setFitness(manager.getCostForTrace(Chromosomes[i].getGenes()));
		}
		std::sort(Chromosomes.begin(), Chromosomes.end(), Better());
	}
	return Chromosomes;
}

//Generuje przyk³adowe odleg³oœci miast.
void generateSampleData(int size, std::string outputFile = "out.tsf") {
	srand(time(NULL));
	std::ofstream tsf(outputFile, std::ofstream::out);
	for (int i = 0; i < size-1; i++)
	{
		for (int j = 0; j < size-1; j++)
		{
			if (i == j) {
				tsf << "0.00 ";
			}
			else {
				tsf << float((rand() % 10000)) / 1000 << '\t';
			}
		}
		tsf << float((rand() % 10000)) / 1000 << '\n';
	}
	for (int j = 0; j < size - 1; j++)
	{
		tsf << float((rand() % 10000)) / 1000 << '\t';
	}
	tsf << "0.00 ";
	tsf.flush();
	tsf.close();
}

int main(int argc, char* argv[])
{
	const clock_t begin_time = clock();
	std::string input, output;
	int cycles=0, chromosomes=0;
	bool executionTimeRequested = false;
	for (int i = 1; i < argc; i++)
	{
		std::string tmp = argv[i];
		if (tmp == "-i") {
			i++;
			input = argv[i];
		}
		else if (tmp == "-o") {
			i++;
			output = argv[i];
		}
		else if (tmp == "-n") {
			i++;
			cycles = std::stoi(argv[i]);
		}
		else if (tmp == "-c") {
			i++;
			chromosomes = std::stoi(argv[i]);
		}
		else if (tmp == "-t") {
			executionTimeRequested = true;
		}
	}

	if (input.empty() && output.empty()) {
		std::cout << "Input file not defined\n\n";
		help();
		return 0;
	}

	if (!input.empty() && cycles < 1) {
		std::cout << "Number of cycles must be > 1\n\n";
		help();
		return 0;
	}
	if (chromosomes < 1) {
		std::cout << "Number of chromosomes must be > 1\n\n";
		help();
		return 0;
	}

	if (!output.empty()) {
		generateSampleData(chromosomes);
		if (input.empty())
			return 0;
	}

	


	std::vector<Chromosome> &OutputData = Operate(input,chromosomes,cycles);
	for (auto it = OutputData[0].getGenes().begin(); it != OutputData[0].getGenes().end(); ++it)
		std::cout << *it<< " ";
	std::cout << OutputData[0].getFitness() << '\n';

	if (executionTimeRequested) {
		std::cout <<"Execution time: " << float(clock() - begin_time) / CLOCKS_PER_SEC << std::endl;
	}

#ifdef _DEBUG
	system("pause");
#endif
	return 0;
}