#ifndef STLVECTOR_H
#define STLVECTOR_H

#include "structurerepresentor.h"
#include <vector>
#include <utility>
#include <algorithm>

using std::vector;
using std::pair;

template<typename K,typename V>
class StlVector: public StructureRepresentor<K,V>
{
public:
    StlVector();
    void insert(K key,V value)override;
    void remove(K key)override;
    int find(K key)override;
    void randomInsert()override;
    void writeDotFile(const char* filename)override;
private:
    vector<pair<K,V>>m_vector;
};

template<typename K,typename V>
StlVector<K,V>::StlVector()
{

}

template<typename K,typename V>
void StlVector<K,V>::insert(K key,V value)
{
    m_vector.emplace_back(key,value);
}

template<typename K,typename V>
void StlVector<K,V>::remove(K key)
{
    auto element = std::find_if(m_vector.begin(),m_vector.end(),[key](const pair<K,V>&pair){return pair.first == key;});
    if(element !=m_vector.end())
    {
        m_vector.erase(element);
    }
}

template<typename K,typename V>
int StlVector<K,V>::find(K key)
{
    auto element = std::find_if(m_vector.begin(),m_vector.end(),[key](const pair<K,V>&pair){return pair.first == key;});
    if(element !=m_vector.end())
    {
        return element->second;
    }
    else
    {
        return int();
    }
}

template<typename K,typename V>
void StlVector<K,V>::randomInsert()
{

}

template<typename K,typename V>
void StlVector<K,V>::writeDotFile(const char *filename)
{
    //std::ofstream fout(filename);


}
#endif // STLVECTOR_H
