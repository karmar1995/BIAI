#ifndef BIAI_IGENETICOPERATOR_H
#define BIAI_IGENETICOPERATOR_H
#define NodeNotChosen -1

#include "Chromosome.h"
#include <map>
#include <vector>

typedef std::map<int, std::vector<int>> EdgeMap;
typedef std::vector<int> GenesVector;
typedef GenesVector EdgesVector;
typedef std::pair<Chromosome, Chromosome> ChromosomePair;

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
    void generateMapForChromosome(const Chromosome &chromosome, EdgeMap& edgeMap);
	void deleteReferencesToNode(int node, EdgeMap& edgeMap);
	Chromosome createOffspring(const Chromosome& parent, EdgeMap EdgeMap);
	EdgeMap generateEdgeMap(const ChromosomePair& parents);
	int PickNode(EdgesVector edgesVector, EdgeMap reducedMap);
public:
    EdgeCrossover();
	ChromosomePair Crossover(const ChromosomePair& parents) override;
};
#endif //BIAI_IGENETICOPERATOR_H
