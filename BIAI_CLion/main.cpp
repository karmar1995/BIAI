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
	std::cout << "Proper program usage: TravellingSalesman <-i File_Path> <-o File_Path> [-t]\
\n\t -i - Input file location\
\n\t -o - Output file location\
\n\t -n - Number of iterations\
\n\t -c - Number of chromosomes\
\n\t -t - Writes execution time at end of output file\n";
}

float Operate(std::string input,int nuberOfChromosomes,int numberOfCycles) {
	srand(time(NULL));
	std::shared_ptr<ICrossover> crossover(new EdgeCrossover);
	//std::shared_ptr<IMutation> mutator(new ScrambleMutation);
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

	const clock_t begin_time = clock();
	for (int j = 0; j < numberOfCycles; j++) {
		for (int i = 0; i < Chromosomes.size(); i++)
		{
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
	return float(clock() - begin_time) / CLOCKS_PER_SEC;
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
				tsf << float((rand() % 1000)) / 100 << '\t';
			}
		}
		tsf << float((rand() % 1000)) / 100 << '\n';
	}
	for (int j = 0; j < size - 1; j++)
	{
		tsf << float((rand() % 1000)) / 100 << '\t';
	}
	tsf << "0.00 ";
	tsf.flush();
	tsf.close();
}

int main(int argc, char* argv[])
{
	std::string input, output;
	int cycles, chromosomes, checkSum=0;
	bool executionTimeRequested = false;
	if (argc == 10 || argc==9) {
		for (int i = 1; i < argc; i++)
		{
			std::string tmp = argv[i];
			if (tmp == "-i") {
				i++;
				checkSum++;
				input = argv[i];
			}
			else if (tmp == "-o") {
				i++;
				checkSum++;
				output = argv[i];
			}
			else if (tmp == "-n") {
				i++;
				checkSum++;
				cycles = std::stoi(argv[i]);
			}
			else if (tmp == "-c") {
				i++;
				checkSum++;
				chromosomes = std::stoi(argv[i]);
			}
			else if (tmp == "-t") {
				executionTimeRequested = true;
			}
		}
	}
	else {
		help();
		system("pause");
		return 0;
	}
	if (checkSum != 4) {
		help();
		system("pause");
		return 0;
	}

	if (input.empty()) {
		std::cout << "Input file not defined\n\n";
		help();
		system("pause");
		return 0;
	}
	if (output.empty()) {
		std::cout << "Output file not defined\n\n";
		help();
		system("pause");
		return 0;
	}

	float Stoper = Operate(input,chromosomes,cycles);

	if (executionTimeRequested) {
		std::cout <<"Execution time: " << Stoper << std::endl;
	}

#ifdef _DEBUG
	system("pause");
#endif
	return 0;
}