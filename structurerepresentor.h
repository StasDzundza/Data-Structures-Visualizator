#ifndef STRUCTUREREPRESENTOR_H
#define STRUCTUREREPRESENTOR_H
#include "officials.h"
#include <iostream>

using std::ostream;

template<typename K,typename V>
class StructureRepresentor{
public:
    enum Type{SplayTree,RedBlack,LinkedList,HashTable,StlList,StlMap,StlVector};
    virtual void insert(K key,V data) = 0;
    virtual void remove(K key) = 0;
    virtual int find(K key) = 0;
    virtual void randomInsert() = 0;
    virtual void writeDotFile(const char* filename) = 0;
    int getType(){return static_cast<int>(type);}
protected:
    Type type;
};
#endif // STRUCTUREREPRESENTOR_H
