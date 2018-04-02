#ifndef BIAI_CHROMOSOME_H
#define BIAI_CHROMOSOME_H

#include <vector>

class Chromosome {
    std::vector<int> m_Genes;
    int m_Length;
public:
    explicit Chromosome(int length);
    explicit Chromosome(std::vector<int> m_Genes);
    const std::vector<int>& getGenes() const;
    void Display();
private:
    void FillEmptyChromosome();
};


#endif //BIAI_CHROMOSOME_H
