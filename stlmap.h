#ifndef STLMAP_H
#define STLMAP_H

#include "structurerepresentor.h"
#include <map>
#include <utility>
#include <fstream>

template<typename K,typename V>
class StlMap: public StructureRepresentor<K,V>{
public:
    StlMap();
    ~StlMap() = default;
    void insert(K key, V value) override;
    void remove(K key) override;
    void clear() override;
    V find(K key) override;
    void randomInsert()override;
    void writeToFile(const char *fileName) override;

    StructureRepresentor<K,V>* Union(const StructureRepresentor<K,V>&s)override;
    StructureRepresentor<K,V>* Intersection(const StructureRepresentor<K,V>&s)override;
    StructureRepresentor<K,V>* SymDiff(const StructureRepresentor<K,V>&s)override;
    StructureRepresentor<K,V>* Diff(const StructureRepresentor<K,V>&s)override;
    vector<K> getKeys()override;
    void sort()override;
private:
    std::map<K,V> m_map;
};


template<typename K, typename V>
StlMap<K,V>::StlMap()
{
    StructureRepresentor<K,V>::type = StructureRepresentor<K,V>::Type::StlMap;
}

template<typename K, typename V>
void StlMap<K,V>::insert(K key, V value)
{
    m_map[key] = value;
}

template<typename K,typename V>
void StlMap<K,V>::remove(K key)
{
    typename std::map<K,V>::const_iterator itr = m_map.find(key);
    if(itr != m_map.end()){
        m_map.erase(itr);
    }
}

template<typename K,typename V>
void StlMap<K,V>::clear()
{
    m_map.clear();
}

template<typename K, typename V>
void StlMap<K,V>::randomInsert()
{

}

template<typename K,typename V>
V StlMap<K,V>::find(K key)
{
    typename std::map<K,V>::const_iterator itr = m_map.find(key);
    if(itr != m_map.end()){
        return itr->second;
    }
    else {
        return V();
    }
}

template<typename K,typename V>
void StlMap<K,V>::writeToFile(const char *fileName)
{
    std::ofstream fout(fileName);
    fout << "digraph{node[shape=record]\n" << std::endl;
    if(!m_map.empty()){
        for(const auto &elem : m_map)
        {
            fout << "      " << (quintptr)&elem;
            fout << "[label=\"";
            fout << "{key: " << elem.first << "|val:" << elem.second << "}";
            fout << "\"];" << std::endl;
        }
        fout << "\n\n";
    }
    fout << "}";
}

template<typename K, typename V>
StructureRepresentor<K, V> *StlMap<K, V>::Union(const StructureRepresentor<K, V> &s)
{

}

template<typename K, typename V>
StructureRepresentor<K, V> *StlMap<K, V>::Intersection(const StructureRepresentor<K, V> &s)
{

}

template<typename K, typename V>
StructureRepresentor<K, V> *StlMap<K, V>::SymDiff(const StructureRepresentor<K, V> &s)
{

}

template<typename K, typename V>
StructureRepresentor<K, V> *StlMap<K,V>::Diff(const StructureRepresentor<K, V> &s)
{

}

template<typename K, typename V>
vector<K> StlMap<K, V>::getKeys()
{

}

template<typename K, typename V>
void StlMap<K,V>::sort()
{

}
#endif // STLMAP_H
