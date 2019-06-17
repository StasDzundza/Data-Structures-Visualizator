#ifndef STLLIST_H
#define STLLIST_H

#include "structurerepresentor.h"
#include <list>
#include <utility>

#include <algorithm>
#include <iostream>
#include <fstream>

using std::list;
using std::pair;
using std::endl;

template<typename K,typename V>
class StlList : public StructureRepresentor<K,V>
{
public:
    StlList();
    void insert(K key,V value)override;
    void remove(K key)override;
    V find(K key)override;
    void randomInsert()override;
    void writeDotFile(const char* filename)override;
    StructureRepresentor<K,V>* Union(StructureRepresentor<K,V>*s)override;
    StructureRepresentor<K,V>* Intersection(StructureRepresentor<K,V>*s)override;
    StructureRepresentor<K,V>* SymDiff(StructureRepresentor<K,V>*s)override;
    StructureRepresentor<K,V>* Diff(StructureRepresentor<K,V>*s)override;
    vector<pair<K,V>> getKeys()override;
    void sort()override;
    void clear()override;
private:
    list<pair<int,int>>list;
};

template<typename K,typename V>
StlList<K,V>::StlList()
{
    StructureRepresentor<K,V>::type = StructureRepresentor<K,V>::Type::StlList;
}

template<typename K,typename V>
void StlList<K,V>::insert(K key,V value)
{
    list.emplace_front(key,value);
}

template<typename K,typename V>
void StlList<K,V>::remove(K key)
{
    auto element = std::find_if(list.begin(),list.end(),[key](const pair<int,int>&pair){return pair.first == key;});
    if(element !=list.end())
    {
        list.erase(element);
    }
}

template<typename K,typename V>
V StlList<K,V>::find(K key)
{
    auto element = std::find_if(list.begin(),list.end(),[key](const pair<int,int>&pair){return pair.first == key;});
    if(element !=list.end())
    {
        return element->second;
    }
    else
    {
        return V();
    }
}

template<typename K,typename V>
void StlList<K,V>::randomInsert()
{

}

template<typename K,typename V>
void StlList<K,V>::writeDotFile(const char *filename)
{
    std::ofstream fout(filename);
    fout << "digraph{node[shape=record]\n" << std::endl;

    if(!list.empty()){
        for(const auto &elem : list)
        {
            fout << "      " << (quintptr)&elem;
            fout << "[label=\"";
            fout << "{key: " << elem.first << "|val:" << elem.second << "}";
            fout << "\"];" << std::endl;
        }
        fout << "\n\n";

        fout << (quintptr)&(*list.begin());
        for(auto itr = ++list.begin(); itr != list.end(); ++itr)
        {
            fout << "->" << (quintptr)&(*itr) << ";\n";
            fout << (quintptr)&(*itr);
        }
        fout << "->end;\n";
    }
    fout << "}";
}

template<typename K, typename V>
StructureRepresentor<K, V> *StlList<K, V>::Union( StructureRepresentor<K, V> *s)
{
    vector<pair<K,V>>p1 = this->getKeys();
    vector<pair<K,V>>p2 = s->getKeys();
    StructureRepresentor<K,V>*sr = new StlList<K,V>;
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
StructureRepresentor<K, V> *StlList<K, V>::Intersection( StructureRepresentor<K, V> *s)
{

}

template<typename K, typename V>
StructureRepresentor<K, V> *StlList<K, V>::SymDiff( StructureRepresentor<K, V> *s)
{

}

template<typename K, typename V>
StructureRepresentor<K, V> *StlList<K, V>::Diff( StructureRepresentor<K, V> *s)
{

}

template<typename K, typename V>
vector<pair<K,V>> StlList<K, V>::getKeys()
{
    vector<pair<K,V>>key_val;
    for(pair<K,V>p:list)
    {
        key_val.emplace_back(p.first,p.second);
    }
    return key_val;
}

template<typename K, typename V>
void StlList<K,V>::sort()
{

}

template<typename K, typename V>
void StlList<K,V>::clear()
{

}
#endif // STLLIST_H
