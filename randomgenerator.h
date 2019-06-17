#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include "structurerepresentor.h"
#include <vector>
#include <QRandomGenerator>

template<typename K, typename V>
class RandomGenerator
{
public:
    RandomGenerator();

    void fillStructureInt(StructureRepresentor<K,V>*s,int amount);

private:
    QRandomGenerator*random;
};

template<typename K, typename V>
RandomGenerator<K,V>::RandomGenerator()
{
    random = new QRandomGenerator;
}

template<typename K, typename V>
void RandomGenerator<K,V>::fillStructureInt(StructureRepresentor<K, V> *s,int amount)
{
    std::vector<int> keys(amount),values(amount);
    random->generate(keys.begin(), keys.end());
    random->generate(values.begin(), values.end());

    while(amount --> 0){
        s->insert(keys[amount-1],values[amount-1]);
    }
}
#endif // RANDOMGENERATOR_H
