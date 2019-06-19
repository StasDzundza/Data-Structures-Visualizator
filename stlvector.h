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
    ~StlVector()override;
    void insert(const K& key,const V& value)override;
    void remove(const K& key)override;
    V find(const K& key)override;
    void writeDotFile(const char* filename)override;
    StructureRepresentor<K,V>* Union(StructureRepresentor<K,V>*s)override;
    StructureRepresentor<K,V>* Intersection(StructureRepresentor<K,V>*s)override;
    StructureRepresentor<K,V>* SymDiff(StructureRepresentor<K,V>*s)override;
    StructureRepresentor<K,V>* Diff(StructureRepresentor<K,V>*s)override;
    vector<pair<K,V>> getKeys()override;
    void sortByKey()override;
    void sortByValue()override;
    void clear()override;
    bool isEmpty()override;
private:
    vector<pair<K,V>>m_vector;
};

template<typename K,typename V>
StlVector<K,V>::StlVector()
{
    StructureRepresentor<K,V>::type = StructureRepresentor<K,V>::Type::StlVector;
}

template<typename K, typename V>
StlVector<K,V>::~StlVector()
{
    clear();
}

template<typename K,typename V>
void StlVector<K,V>::insert(const K& key,const V& value)
{
    m_vector.emplace_back(key,value);
}

template<typename K,typename V>
void StlVector<K,V>::remove(const K& key)
{
    auto element = std::find_if(m_vector.begin(),m_vector.end(),[key](const pair<K,V>&pair){return pair.first == key;});
    if(element !=m_vector.end())
    {
        m_vector.erase(element);
    }
}

template<typename K,typename V>
V StlVector<K,V>::find(const K& key)
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
StructureRepresentor<K, V> *StlVector<K,V>::Union( StructureRepresentor<K, V> *s)
{
    vector<pair<K,V>>p1 = this->getKeys();
    vector<pair<K,V>>p2 = s->getKeys();
    StructureRepresentor<K,V>*sr = new StlVector<K,V>;
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
StructureRepresentor<K, V> *StlVector<K,V>::Intersection( StructureRepresentor<K, V> *s)
{
    vector<pair<K,V>>p1 = this->getKeys();
    vector<pair<K,V>>p2 = s->getKeys();
    StructureRepresentor<K,V>*I = new StlVector<K,V>;
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
StructureRepresentor<K, V> *StlVector<K,V>::SymDiff( StructureRepresentor<K, V> *s)
{
    StructureRepresentor<K, V> *inters = this->Intersection(s);
    StructureRepresentor<K, V> *diff1 = this->Diff(inters);
    StructureRepresentor<K, V> *diff2 = s->Diff(inters);
    StructureRepresentor<K, V> *res = diff1->Union(diff2);
    delete inters,diff1,diff2;
    return res;

}

template<typename K, typename V>
StructureRepresentor<K, V> *StlVector<K,V>::Diff( StructureRepresentor<K, V> *s)
{
    vector<pair<K,V>>p1 = this->getKeys();
    vector<pair<K,V>>p2 = s->getKeys();
    StructureRepresentor<K,V>*D = new StlVector<K,V>;
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
vector<pair<K,V>> StlVector<K,V>::getKeys()
{
    vector<pair<K,V>>key_val;
    for(pair<K,V>p:m_vector)
    {
        key_val.emplace_back(p.first,p.second);
    }
    return key_val;
}

template<typename K, typename V>
void StlVector<K,V>::sortByValue()
{

}

template<typename K, typename V>
void StlVector<K,V>::sortByKey()
{

}

template<typename K, typename V>
void StlVector<K,V>::clear()
{
    m_vector.clear();
}

template<typename K, typename V>
bool StlVector<K,V>::isEmpty()
{
    m_vector.empty();
}
#endif // STLVECTOR_H
