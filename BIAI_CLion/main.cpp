#include <iostream>
#include <cstdlib>
#include <time.h>
#include "IGeneticOperator.h"
#include "GraphManager.h"
#include <memory>
#include <algorithm>
#include <iostream>
#include <iterator>

int main()
{
    srand(time(NULL));
	std::shared_ptr<ICrossover> crossover (new EdgeCrossover);
	std::shared_ptr<IMutation> mutator (new ScrambleMutation);
	ChromosomePair parents = std::make_pair(Chromosome(10), Chromosome(10));
	ChromosomePair offsprings = crossover->Crossover(parents);
	offsprings.first.Display();
	offsprings.second.Display();
#ifdef _DEBUG
	system("pause");
#endif
	return 0;
}