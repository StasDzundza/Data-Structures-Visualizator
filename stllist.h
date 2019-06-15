#ifndef STLLIST_H
#define STLLIST_H

#include "structurerepresentor.h"
#include <list>
#include <utility>

using std::list;
using std::pair;

class StlList : StructureRepresentor
{
public:
    StlList();
    void insert(int key,int data)override;
    void remove(int key)override;
    int find(int key)override;
    void randomInsert()override;
private:
    list<pair<int,int>>list;

};

#endif // STLLIST_H
