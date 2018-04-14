#include <cstdlib>
#include "IGeneticOperator.h"
#include <stdexcept>
#include <algorithm>
#include <list>
#include <iostream>
#include <iterator>

void PrintMap(EdgeMap edgeMap)
{
	for (auto it : edgeMap)
	{
		std::cout << it.first << " edeges: ";
		for (auto node : it.second)
			std::cout << node << " ";
		std::cout << std::endl;
	}
}

ScrambleMutation::ScrambleMutation() {}

Chromosome ScrambleMutation::Mutate(const Chromosome &toMutate)
{
	GenesVector genes = toMutate.getGenes();
    int length = static_cast<int>(genes.size());
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

EdgeCrossover::EdgeCrossover() {}

void EdgeCrossover::generateMapForChromosome(const Chromosome &chromosome, EdgeMap& edgeMap)
{
	GenesVector genes = chromosome.getGenes();
    for(auto it = genes.begin(); it<genes.end(); ++it)
    {
        int gene = *it;
        auto pNext = (it == (genes.end()-1)) ? genes.begin() : it+1;
        auto pPrev = (it == genes.begin()) ? genes.end()-1 : it-1;
		edgeMap[gene].push_back(*(pPrev));
		edgeMap[gene].push_back(*(pNext));
    }
}

void EdgeCrossover::deleteReferencesToNode(int node, EdgeMap& edgeMap)
{
	for (auto edgeMapIterator : edgeMap)
	{
		std::vector<int> newEdgeVector;
		auto it = std::copy_if(
			edgeMapIterator.second.begin(), edgeMapIterator.second.end(),
			std::back_inserter(newEdgeVector), 
			[node](int i) 
			{
				return i != node;
			} 
		);
		edgeMap[edgeMapIterator.first] = newEdgeVector;
	}
}

int EdgeCrossover::PickNode(EdgesVector edgesVector, EdgeMap reducedMap)
{
	if (!edgesVector.empty())
	{
		std::sort(edgesVector.begin(), edgesVector.end());
		auto it = std::adjacent_find(edgesVector.begin(), edgesVector.end());
		if ( it != edgesVector.end())
			return *it; // pick the first found duplicate
		else
		{
			std::pair<int, int> curMin(255, 255);
			for (auto node : edgesVector)
			{
				if (reducedMap.at(node).size() < curMin.second)
					curMin = std::make_pair(node, reducedMap[node].size());
				else if(reducedMap.at(node).size() == curMin.second)
					curMin = rand()%2==0? curMin: std::make_pair(node, reducedMap[node].size());
			}
			return curMin.first; //pick randomly chosen node with shortest edges vector
		}
	}
	return NodeNotChosen;
}




Chromosome EdgeCrossover::createOffspring(const Chromosome & parent, EdgeMap edgeMap)
{
	GenesVector parentGenes = parent.getGenes();
	int size = static_cast<int>(parentGenes.size());
	Chromosome offspring(size, true);
	offspring[--size] = parentGenes[size];
	deleteReferencesToNode(parentGenes[size], edgeMap);
	int node = parent.getGenes()[rand() % size];
	int reversedIndex = size;
	for (int i = 0; i < size; i++)
	{
		offspring[i] = node;
		deleteReferencesToNode(node, edgeMap);
		node = PickNode(edgeMap.at(node), edgeMap);
		if (node == NodeNotChosen)
		{
			node = PickNode(edgeMap.at(offspring[reversedIndex]), edgeMap);
			if (node == NodeNotChosen)
			{
				GenesVector tmp;
				auto it = std::copy_if(
					parentGenes.begin(), parentGenes.end(),
					std::back_inserter(tmp),
					[offspring](int i){
						for (int j : offspring.getGenes())
							if (j == i)	return false;
						return true; });
				if (tmp.size() > 0)
					node = tmp[rand()%tmp.size()];
 
			}
		}
	}
	return offspring;
}



EdgeMap EdgeCrossover::generateEdgeMap(const ChromosomePair& parents)
{
	EdgeMap edgeMap;
    generateMapForChromosome(parents.first, edgeMap);
    generateMapForChromosome(parents.second, edgeMap);
#ifdef _DEBUG
	std::cout << "\nParent 1: ";
	parents.first.Display();
	std::cout << "\nParent 2: ";
	parents.second.Display();
	std::cout << "\nCreated original map\n" << std::endl;
	PrintMap(edgeMap);
	std::cout << "\n===================\n" << std::endl;
#endif
	return edgeMap;
}

ChromosomePair EdgeCrossover::Crossover(const ChromosomePair& parents)
{
	EdgeMap edgeMap = generateEdgeMap(parents);
    return std::make_pair(createOffspring(parents.first, edgeMap), createOffspring(parents.second, edgeMap));
}




