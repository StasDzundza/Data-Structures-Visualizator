#ifndef DRAWER_H
#define DRAWER_H

#include <map>
#include <string>
#include "structurerepresentor.h"
#include "stllist.h"
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QDebug>

using std::string;
using std::map;

template<typename K,typename V>
class Drawer
{
public:
    Drawer();

    QImage createPngImage(StructureRepresentor<K,V>*s);
private:
    map<int,std::string> path;
};

template<typename K,typename V>
Drawer<K,V>::Drawer()
{
    path = {{0,"..\\DataStructures Visualizator\\Output\\SplayTree\\"},{1,"..\\DataStructures Visualizator\\Output\\RedBlack\\"},{2,"..\\DataStructures Visualizator\\Output\\LinkedList\\"},{3,"..\\DataStructures Visualizator\\Output\\StlList\\"}};
}

template<typename K,typename V>
QImage Drawer<K,V>::createPngImage(StructureRepresentor<K,V> *s)
{
    string pathToFile ="";// path[s->getType()];
    string pathToImage= pathToFile;
    pathToFile+="structure.dot";
    pathToImage+="structure.png";

    qDebug()<<pathToFile.c_str();
    qDebug()<<pathToImage.c_str();
    s->writeDotFile(pathToFile.c_str());
    string commanStr = "";
    commanStr += "..\\DataStructuresVisualizator\\graphviz\\bin\\dot.exe -Tpng " + pathToFile + " -o " + pathToImage;
    system(commanStr.c_str());
    QImage image(pathToImage.c_str());

    return image;
}
#endif // DRAWER_H
