#include "stllist.h"
#include <algorithm>
StlList::StlList()
{

}

void StlList::insert(int key,int data)
{
    list.emplace_front(key,data);
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
