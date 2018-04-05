#ifndef BIAI_IGENETICOPERATOR_H
#define BIAI_IGENETICOPERATOR_H

#include "Chromosome.h"
#include <map>
#include <vector>
class IMutation
{
public:
    virtual Chromosome Mutate(const Chromosome& toMutate) = 0;
};

class ICrossover
{
public:
    virtual std::pair<Chromosome, Chromosome> Crossover(const std::pair<Chromosome, Chromosome>& parents) = 0;
};

class ScrambleMutation: public IMutation
{
public:
    ScrambleMutation();
    Chromosome Mutate(const Chromosome& toMutate) override;
};

class EdgeCrossover: public ICrossover
{
    void generateMapForChromosome(const Chromosome &chromosome, std::map<int, std::vector<int>>& EdgeMap);
    std::map<int, std::vector<int>> generateEdgeMap(const std::pair<Chromosome, Chromosome>& parents);
public:
    EdgeCrossover();
    std::pair<Chromosome, Chromosome> Crossover(const std::pair<Chromosome, Chromosome>& parents) override;
};
#endif //BIAI_IGENETICOPERATOR_H
