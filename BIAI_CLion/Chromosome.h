#ifndef BIAI_CHROMOSOME_H
#define BIAI_CHROMOSOME_H

#include <vector>

class Chromosome {
    std::vector<int> m_Genes;
    int m_Length;
	double m_Fitness;
public:
    explicit Chromosome(int length, bool empty=false);
	explicit Chromosome(std::vector<int> m_Genes);
    const std::vector<int>& getGenes() const;
    void Display() const;
	void setFitness(double fitness);
	double getFitness() const;
	int& operator[](int index);
private:
    void FillEmptyChromosome();
};

struct Better
{
	inline bool operator() (const Chromosome& struct1, const Chromosome& struct2)
	{
		return (struct1.getFitness() < struct2.getFitness());
	}
};

#endif //BIAI_CHROMOSOME_H
