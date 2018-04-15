#include <iostream>
#include <cstdlib>
#include <time.h>
#include "IGeneticOperator.h"
#include "GraphManager.h"
#include <memory>
#include <algorithm>
#include <iostream>
#include <iterator>

void help() {
	std::cout << "Proper program usage: TravellingSalesman <-i File_Path> <-o File_Path> [-t]\
\n\t -i - Input file location\
\n\t -o - Output file location\
\n\t -t - Writes execution time at end of output file\n";
}

int main(int argc, char* argv[])
{
	std::string input, output;
	bool executionTimeRequested = false;
	if (argc == 6 || argc==5) {
		for (int i = 1; i < argc - 1; i++)
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
			else if (tmp == "-t") {
				executionTimeRequested = true;
			}
		}
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

    srand(time(NULL));
	std::shared_ptr<ICrossover> crossover (new EdgeCrossover);
	std::shared_ptr<IMutation> mutator (new ScrambleMutation);
	ChromosomePair parents = std::make_pair(Chromosome(10), Chromosome(10));
	ChromosomePair offsprings = crossover->Crossover(parents);
	offsprings.first.Display();
	offsprings.second.Display();
	/* Debug purpose only
	GraphFileParser ts("Map.tsf");
	ts.ParseFile();
	*/
#ifdef _DEBUG
	system("pause");
#endif
	return 0;
}