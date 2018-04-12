#include <iostream>
#include "Chromosome.h"
#include <algorithm>

Chromosome::Chromosome(int length, bool empty)
{
    m_Genes.resize(length);
    m_Length = length;
	if(!empty)
	    FillEmptyChromosome();
}

Chromosome::Chromosome(std::vector<int> genes)
{
    m_Genes = genes;
}

const std::vector<int> &Chromosome::getGenes() const
{
    return m_Genes;
}

void Chromosome::FillEmptyChromosome()
{
    for(int i = 1; i <= m_Length; i++)
    {
        m_Genes[i-1] = i;
    }
    std::random_shuffle(m_Genes.begin(), m_Genes.end());
}

void Chromosome::Display() const
{
    for(auto gene : m_Genes)
    {
        std::cout<<gene<<" ";
    }
    std::cout<<std::endl;

}

int & Chromosome::operator[](int index)
{
	return m_Genes[index];
}
