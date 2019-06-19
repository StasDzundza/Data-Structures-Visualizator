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
    ~StlList()override;
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
    list<pair<int,int>>list;
};

template<typename K,typename V>
StlList<K,V>::StlList()
{
    StructureRepresentor<K,V>::type = StructureRepresentor<K,V>::Type::StlList;
}

template<typename K, typename V>
StlList<K,V>::~StlList()
{
    clear();
}

template<typename K,typename V>
void StlList<K,V>::insert(const K& key,const V& value)
{
    list.emplace_front(key,value);
}

template<typename K,typename V>
void StlList<K,V>::remove(const K& key)
{
    auto element = std::find_if(list.begin(),list.end(),[key](const pair<int,int>&pair){return pair.first == key;});
    if(element !=list.end())
    {
        list.erase(element);
    }
}

template<typename K,typename V>
V StlList<K,V>::find(const K& key)
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
    vector<pair<K,V>>p1 = this->getKeys();
    vector<pair<K,V>>p2 = s->getKeys();
    StructureRepresentor<K,V>*I = new StlList<K,V>;
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
StructureRepresentor<K, V> *StlList<K, V>::SymDiff( StructureRepresentor<K, V> *s)
{
    StructureRepresentor<K, V> *inters = this->Intersection(s);
    StructureRepresentor<K, V> *diff1 = this->Diff(inters);
    StructureRepresentor<K, V> *diff2 = s->Diff(inters);
    StructureRepresentor<K, V> *res = diff1->Union(diff2);
    delete inters,diff1,diff2;
    return res;
}

template<typename K, typename V>
StructureRepresentor<K, V> *StlList<K, V>::Diff( StructureRepresentor<K, V> *s)
{
    vector<pair<K,V>>p1 = this->getKeys();
    vector<pair<K,V>>p2 = s->getKeys();
    StructureRepresentor<K,V>*D = new StlList<K,V>;
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
void StlList<K,V>::sortByKey()
{
    list.sort([](const pair<K,V>&p1,const pair<K,V>&p2){return p1.first > p2.first;});
}

template<typename K, typename V>
void StlList<K,V>::sortByValue()
{
    list.sort([](const pair<K,V>&p1,const pair<K,V>&p2){return p1.second > p2.second;});
}

template<typename K, typename V>
void StlList<K,V>::clear()
{
    list.clear();
}

template<typename K, typename V>
bool StlList<K,V>::isEmpty()
{
    return list.empty();
}
#endif // STLLIST_H
