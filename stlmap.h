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
    void writeDotFile(const char *fileName) override;

    StructureRepresentor<K,V>* Union(StructureRepresentor<K,V>*s)override;
    StructureRepresentor<K,V>* Intersection(StructureRepresentor<K,V>*s)override;
    StructureRepresentor<K,V>* SymDiff(StructureRepresentor<K,V>*s)override;
    StructureRepresentor<K,V>* Diff(StructureRepresentor<K,V>*s)override;
    vector<pair<K,V>> getKeys()override;
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
void StlMap<K,V>::writeDotFile(const char *fileName)
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
StructureRepresentor<K, V> *StlMap<K, V>::Union( StructureRepresentor<K, V> *s)
{
    vector<pair<K,V>>p1 = this->getKeys();
    vector<pair<K,V>>p2 = s->getKeys();
    StructureRepresentor<K,V>*sr = new StlMap<K,V>;
    for(pair<K,V>p:p1)
    {
        sr->insert(p.first,p.second);
    }
    for(pair<K,V>p:p2)
    {
        sr->insert(p.first,p.second);
    }
    return sr;
}

template<typename K, typename V>
StructureRepresentor<K, V> *StlMap<K, V>::Intersection( StructureRepresentor<K, V> *s)
{
    vector<pair<K,V>>p1 = this->getKeys();
    vector<pair<K,V>>p2 = s->getKeys();
    StructureRepresentor<K,V>*I = new StlMap<K,V>;
    for(pair<K,V>p:p1)
    {
        auto element = std::find_if(p2.begin(),p2.end(),[p](const pair<int,int>&pair){return pair.second == p.second;});
        if(element !=p2.end())
        {
            I->insert(element->first,element->second);
        }
    }
    return I;
}

template<typename K, typename V>
StructureRepresentor<K, V> *StlMap<K, V>::SymDiff( StructureRepresentor<K, V> *s)
{
    StructureRepresentor<K, V> *inters = this->Intersection(s);
    StructureRepresentor<K, V> *diff1 = this->Diff(inters);
    StructureRepresentor<K, V> *diff2 = s->Diff(inters);
    StructureRepresentor<K, V> *res = diff1->Union(diff2);
    return res;
}

template<typename K, typename V>
StructureRepresentor<K, V> *StlMap<K,V>::Diff( StructureRepresentor<K, V> *s)
{
    vector<pair<K,V>>p1 = this->getKeys();
    vector<pair<K,V>>p2 = s->getKeys();
    StructureRepresentor<K,V>*D = new StlMap<K,V>;
    for(pair<K,V>p:p1)
    {
        auto element = std::find_if(p2.begin(),p2.end(),[p](const pair<int,int>&pair){return pair.second == p.second;});
        if(element == p2.end())
        {
            D->insert(p.first,p.second);
        }
    }
    return D;
}

template<typename K, typename V>
vector<pair<K,V>> StlMap<K, V>::getKeys()
{
    vector<pair<K,V>>key_val;
    for(pair<K,V>p:m_map)
    {
        key_val.emplace_back(p.first,p.second);
    }
    return key_val;
}

template<typename K, typename V>
void StlMap<K,V>::sort()
{
    m_map.clear();
}
#endif // STLMAP_H
