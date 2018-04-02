#ifndef BIAI_IGENETICOPERATOR_H
#define BIAI_IGENETICOPERATOR_H

#include "Chromosome.h"


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

#endif //BIAI_IGENETICOPERATOR_H
