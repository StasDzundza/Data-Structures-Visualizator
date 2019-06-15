#ifndef COREFACADE_H
#define COREFACADE_H

#include <QGraphicsView>

class StructureRepresentor;
class CoreFacade
{
public:
    CoreFacade();

    void insert(int key,int value, int structureIndex);
    void drawStructure(int struct_index,QGraphicsView *view);

private:
    StructureRepresentor*s1,*s2;
    StructureRepresentor*getStructureFromIndex(int struct_index);
};

#endif // COREFACADE_H
