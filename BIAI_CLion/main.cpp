#include <iostream>
#include "IGeneticOperator.h"

int main()
{
    srand(time(NULL));
    Chromosome test(10);
    ScrambleMutation mutator;
    for(int i = 0; i < 10; i++)
    {
        test.Display();
        test = mutator.Mutate(test);
    }

    return 0;
}