#include "corefacade.h"
#include "structurerepresentor.h"

CoreFacade::CoreFacade()
{

}

void CoreFacade::insert(int key, int value, int struct_index)
{
    StructureRepresentor*s = getStructureFromIndex(struct_index);
    s->insert(key,value);
}

void CoreFacade::drawStructure(int struct_index, QGraphicsView *view)
{
    StructureRepresentor*s = getStructureFromIndex(struct_index);

}

StructureRepresentor *CoreFacade::getStructureFromIndex(int struct_index)
{
    StructureRepresentor*s = nullptr;
    if(struct_index == 1)
    {
        s = s1;
    }
    else
    {
        s = s2;
    }
    return s;
}
