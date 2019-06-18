#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include "structurerepresentor.h"
#include <vector>
#include <QRandomGenerator>
#include <QDebug>

template<typename K, typename V>
class RandomGenerator
{
public:
    RandomGenerator();

    void fillStructureInt(StructureRepresentor<K,V>*s,int amount);

    void fillVector(std::vector<int>&vec,int amount);

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
    std::vector<int> keys,values;

    fillVector(keys,amount);
    fillVector(values,amount);

    for(int i = 0; i < amount;i++)
        s->insert(keys[i],values[i]);
}

template<typename K, typename V>
void RandomGenerator<K,V>::fillVector(std::vector<int> &vec,int amount)
{
    for(int i = 0; i < amount; i++)
    {
        qDebug()<<QRandomGenerator::global()->bounded(-200,200);
        vec.push_back(QRandomGenerator::global()->bounded(-200,200));
    }
}
#endif // RANDOMGENERATOR_H
