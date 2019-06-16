#ifndef STRUCTUREREPRESENTOR_H
#define STRUCTUREREPRESENTOR_H
#include "officials.h"
#include <iostream>
#include <vector>

//using std::ostream;
using std::vector;

template<typename K,typename V>
class StructureRepresentor{
public:
    enum Type{SplayTree,RedBlack,LinkedList,HashTable,StlList,StlMap,StlVector};
    virtual void insert(K key,V data) = 0;
    virtual void remove(K key) = 0;
    virtual V find(K key) = 0;
    virtual void randomInsert() = 0;
    virtual void writeDotFile(const char* filename) = 0;
    int getType(){return static_cast<int>(type);}

    virtual StructureRepresentor<K,V>* Union(const StructureRepresentor<K,V>&s) = 0;

    virtual StructureRepresentor<K,V>* Intersection(const StructureRepresentor<K,V>&s) = 0;

    virtual StructureRepresentor<K,V>* SymDiff(const StructureRepresentor<K,V>&s) = 0;

    virtual StructureRepresentor<K,V>* Diff(const StructureRepresentor<K,V>&s) = 0;

    virtual vector<K> getKeys() = 0;

    virtual void sort() = 0;
protected:
    Type type;
};
#endif // STRUCTUREREPRESENTOR_H
