#include <iostream>
#include "Chromosome.h"

Chromosome::Chromosome(int length)
{
    m_Genes.resize(length);
    m_Length = length;
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
}

void Chromosome::Display()
{
    for(auto gene : m_Genes)
    {
        std::cout<<gene<<" ";
    }
    std::cout<<std::endl;

}
