#include "stllist.h"
#include <algorithm>
#include <iostream>
#include <fstream>

StlList::StlList()
{

}

void StlList::insert(int key,int value)
{
    list.emplace_front(key,value);
}

void StlList::remove(int key)
{
    auto element = std::find_if(list.begin(),list.end(),[key](const pair<int,int>&pair){return pair.first == key;});
    if(element !=list.end())
    {
        list.erase(element);
    }
}

int StlList::find(int key)
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

void StlList::randomInsert()
{

}

void StlList::writeDotFile(const char *filename)
{
    //std::ofstream fout(filename);


}
