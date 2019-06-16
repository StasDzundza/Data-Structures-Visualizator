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
    int find(K key)override;
    void randomInsert()override;
    void writeDotFile(const char* filename)override;
private:
    list<pair<int,int>>list;

};

template<typename K,typename V>
StlList<K,V>::StlList()
{

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
int StlList<K,V>::find(K key)
{
    auto element = std::find_if(list.begin(),list.end(),[key](const pair<int,int>&pair){return pair.first == key;});
    if(element !=list.end())
    {
        return element->second;
    }
    else
    {
        return int();
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
    fout << "digraph{"<<endl;
    for(const pair<K,V>& pair : list)
    {
        fout << pair.second << "->";
    }

    fout << "end;" << endl;
    fout << "}";
}
#endif // STLLIST_H
