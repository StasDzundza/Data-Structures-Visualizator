#ifndef STRUCTUREREPRESENTOR_H
#define STRUCTUREREPRESENTOR_H
#include "officials.h"
#include <iostream>
#include <vector>
#include <utility>
#include <stack>

using std::pair;
using std::vector;
using std::stack;

template<typename K,typename V>
class StructureRepresentor{
public:
    enum Type{SplayTree,RedBlack,LinkedList,HashTable,StlList,StlMap,StlVector};
    virtual void insert(K key,V data) = 0;
    virtual void remove(K key) = 0;
    virtual V find(K key) = 0;
    virtual void writeDotFile(const char* filename) = 0;
    int getType(){return static_cast<int>(type);}

    virtual StructureRepresentor<K,V>* Union( StructureRepresentor<K,V>*s) = 0;

    virtual StructureRepresentor<K,V>* Intersection( StructureRepresentor<K,V>*s) = 0;

    virtual StructureRepresentor<K,V>* SymDiff( StructureRepresentor<K,V>*s) = 0;

    virtual StructureRepresentor<K,V>* Diff( StructureRepresentor<K,V>*s) = 0;

    virtual vector<pair<K,V>> getKeys() = 0;

    virtual void sort() = 0;

    virtual void clear() = 0;

    virtual bool isEmpty() = 0;
protected:
    Type type;
};
#endif // STRUCTUREREPRESENTOR_H
