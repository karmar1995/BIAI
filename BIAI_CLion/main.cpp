#include <iostream>
#include "IGeneticOperator.h"

int main()
{
    srand(time(NULL));
    Chromosome p1 (10);
    Chromosome p2 (10);
    EdgeCrossover crossover;
    crossover.Crossover(std::pair<Chromosome, Chromosome>(p1,p2));
    return 0;
}