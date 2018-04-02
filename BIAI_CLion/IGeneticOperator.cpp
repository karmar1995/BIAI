#include <cstdlib>
#include "IGeneticOperator.h"
#include <stdexcept>
#include <algorithm>

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
