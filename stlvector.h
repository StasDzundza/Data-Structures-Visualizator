#ifndef STLVECTOR_H
#define STLVECTOR_H

#include "structurerepresentor.h"
#include <vector>
#include <utility>
#include <algorithm>
#include <fstream>

using std::vector;
using std::pair;

template<typename K,typename V>
class StlVector: public StructureRepresentor<K,V>
{
public:
    StlVector();
    void insert(K key,V value)override;
    void remove(K key)override;
    V find(K key)override;
    void randomInsert()override;
    void writeDotFile(const char* filename)override;
    StructureRepresentor<K,V>* Union(const StructureRepresentor<K,V>&s)override;
    StructureRepresentor<K,V>* Intersection(const StructureRepresentor<K,V>&s)override;
    StructureRepresentor<K,V>* SymDiff(const StructureRepresentor<K,V>&s)override;
    StructureRepresentor<K,V>* Diff(const StructureRepresentor<K,V>&s)override;
    vector<K> getKeys()override;
    void sort()override;
    void clear()override;
private:
    vector<pair<K,V>>m_vector;
};

template<typename K,typename V>
StlVector<K,V>::StlVector()
{
    StructureRepresentor<K,V>::type = StructureRepresentor<K,V>::Type::StlVector;
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
V StlVector<K,V>::find(K key)
{
    auto element = std::find_if(m_vector.begin(),m_vector.end(),[key](const pair<K,V>&pair){return pair.first == key;});
    if(element !=m_vector.end())
    {
        return element->second;
    }
    else
    {
        return V();
    }
}

template<typename K,typename V>
void StlVector<K,V>::randomInsert()
{

}

template<typename K,typename V>
void StlVector<K,V>::writeDotFile(const char *filename)
{
    std::ofstream fout(filename);
    fout << "digraph{node[shape=record]\n" << std::endl;

    if(!m_vector.empty()){
        for(const auto &elem : m_vector)
        {
            fout << "      " << (quintptr)&elem;
            fout << "[label=\"";
            fout << "{key: " << elem.first << "|val:" << elem.second << "}";
            fout << "\"];" << std::endl;
        }
        fout << "\n\n";

        fout << (quintptr)&(*m_vector.begin());
        for(auto itr = ++m_vector.begin(); itr != m_vector.end(); ++itr)
        {
            fout << "->" << (quintptr)&(*itr) << ";\n";
            fout << (quintptr)&(*itr);
        }
        fout << "->end;\n";
    }
    fout << "}";
}

template<typename K, typename V>
StructureRepresentor<K, V> *StlVector<K,V>::Union(const StructureRepresentor<K, V> &s)
{

}

template<typename K, typename V>
StructureRepresentor<K, V> *StlVector<K,V>::Intersection(const StructureRepresentor<K, V> &s)
{

}

template<typename K, typename V>
StructureRepresentor<K, V> *StlVector<K,V>::SymDiff(const StructureRepresentor<K, V> &s)
{

}

template<typename K, typename V>
StructureRepresentor<K, V> *StlVector<K,V>::Diff(const StructureRepresentor<K, V> &s)
{

}

template<typename K, typename V>
vector<K> StlVector<K,V>::getKeys()
{

}

template<typename K, typename V>
void StlVector<K,V>::sort()
{

}

template<typename K, typename V>
void StlVector<K,V>::clear()
{

}
#endif // STLVECTOR_H
