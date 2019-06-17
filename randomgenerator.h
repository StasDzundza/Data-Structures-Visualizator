#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include "structurerepresentor.h"

class RandomGenerator
{
public:
    RandomGenerator();

    template<typename K,typename V>
    void fillStructureInt(StructureRepresentor<K,V>*s);
};

#endif // RANDOMGENERATOR_H
