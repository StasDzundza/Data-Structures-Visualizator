#ifndef STRUCTUREREPRESENTOR_H
#define STRUCTUREREPRESENTOR_H
#include "officials.h"
#include <iostream>

using std::ostream;

class StructureRepresentor{
public:
    enum Type{SplayTree,BPlus,LinkedList,HashTable,StlList,StlMap,StlVector};
    virtual void insert(int key,int data) = 0;
    virtual void remove(int key) = 0;
    virtual int find(int key) = 0;
    virtual void randomInsert() = 0;
    virtual void writeDotFile(const char* filename) = 0;
    int getType(){return static_cast<int>(type);}
protected:
    Type type;
};
#endif // STRUCTUREREPRESENTOR_H
