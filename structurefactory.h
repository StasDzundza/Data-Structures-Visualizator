#ifndef STRUCTUREFACTORY_H
#define STRUCTUREFACTORY_H

#include <QString>
#include "stllist.h"
#include "stlvector.h"
#include "stlmap.h"
#include "list.h"
#include "splaytree.h"
#include "osrbtree.h"

class StructureFactory{
private:
    StructureFactory() = default;
    static StructureFactory* instance;
public:
    static StructureFactory *getInstance()
    {
        if(!instance){
            instance = new StructureFactory();
        }
        return instance;
    }
    StructureRepresentor<int,int> *createStructure(const QString& name)
    {
        StructureRepresentor<int,int> *res = nullptr;
        if(name == "StlList")
            res = new StlList<int,int>;
        else if(name == "StlMap")
            res = new StlMap<int,int>;
        else if(name == "StlVector")
            res = new StlVector<int,int>;
        else if(name == "Custom List")
            res = new List<int,int>;
        else if(name == "SplayTree")
            res = new Splay_Tree<int,int>;
        else if(name == "Red-Black Tree")
            res = new OSTreeRB<int,int>;
        return res;
    }
};




#endif // STRUCTUREFACTORY_H
