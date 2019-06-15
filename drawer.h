#ifndef DRAWER_H
#define DRAWER_H

#include <map>
#include <string>
#include "structurerepresentor.h"
#include "stllist.h"
#include <QImage>
#include <QGraphicsView>

using std::string;
using std::map;

class Drawer
{
public:
    Drawer();
    QImage createPngImage(StructureRepresentor*s,QGraphicsView*view);
private:
    map<int,std::string> path;
};

#endif // DRAWER_H
