#include <iostream>
#include <cstdlib>
#include <time.h>
#include "IGeneticOperator.h"
#include "GraphNode.h"
#include <memory>

int main()
{
    srand(time(NULL));
    Chromosome p1 (10);
    Chromosome p2 (10);
	std::shared_ptr<ICrossover> crossover (new EdgeCrossover);
	std::shared_ptr<IMutation> mutator (new ScrambleMutation);
	ChromosomePair offsprings = crossover->Crossover(std::pair<Chromosome, Chromosome>(p1,p2));
	offsprings.first.Display();
	offsprings.second.Display();
	system("pause");
	return 0;
}