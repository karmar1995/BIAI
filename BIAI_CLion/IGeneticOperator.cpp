#include <cstdlib>
#include "IGeneticOperator.h"
#include <stdexcept>
#include <algorithm>
#include <list>

ScrambleMutation::ScrambleMutation()
{

}

Chromosome ScrambleMutation::Mutate(const Chromosome &toMutate)
{
    std::vector<int> genes = toMutate.getGenes();
    int length = genes.size();
    const int swaps = 3;
    for(int i = 0; i < swaps; i++)
    {
        int elem1 = rand()%length;
        int elem2 = rand()%length;
        auto toSwap1 = genes.begin()+=elem1;
        auto toSwap2 = genes.begin()+=elem2;
        std::iter_swap(toSwap1, toSwap2);
    }
    return Chromosome(genes);
}

EdgeCrossover::EdgeCrossover() {

}

void EdgeCrossover::generateMapForChromosome(const Chromosome &chromosome, std::map<int, std::vector<int>>& EdgeMap) {
    std::vector<int> genes = chromosome.getGenes();
    for(auto it = genes.begin(); it<genes.end(); ++it)
    {
        int gene = *it;
        auto pNext = (it == (genes.end()-1)) ? genes.begin() : it+1;
        auto pPrev = (it == genes.begin()) ? genes.end()-1 : it-1;
        EdgeMap[gene].push_back(*(pPrev));
        EdgeMap[gene].push_back(*(pNext));
    }
}

std::map<int, std::vector<int>> EdgeCrossover::generateEdgeMap(const std::pair<Chromosome, Chromosome> &parents) {
    std::map<int, std::vector<int>> EdgeMap;
    generateMapForChromosome(parents.first, EdgeMap);
    generateMapForChromosome(parents.second, EdgeMap);
    return EdgeMap;
}


std::pair<Chromosome, Chromosome> EdgeCrossover::Crossover(const std::pair<Chromosome, Chromosome> &parents)
{
    generateEdgeMap(parents);
    return parents;
}




