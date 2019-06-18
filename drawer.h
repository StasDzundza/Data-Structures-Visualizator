#ifndef DRAWER_H
#define DRAWER_H

#include <map>
#include <string>
#include <QImage>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QDebug>
#include "structurerepresentor.h"
#include <QTextStream>
#include <QFile>

using std::string;
using std::map;


template<typename K,typename V>
class Drawer
{
public:
    Drawer();

    QImage createPngImage(StructureRepresentor<K,V>*s);

    void setPathToGraphvizDotFile(QString graphVizPath);
private:
     QString graphVizPath;
};

template<typename K,typename V>
Drawer<K,V>::Drawer()
{
    graphVizPath = "..\\DataStructuresVisualizator\\graphviz\\bin\\dot.exe";
}

template<typename K,typename V>
QImage Drawer<K,V>::createPngImage(StructureRepresentor<K,V> *s)
{
    string pathToFile ="";
    string pathToImage= pathToFile;
    pathToFile+="structure.dot";
    pathToImage+="structure.png";
    s->writeDotFile(pathToFile.c_str());
    QString cmdCommand = QString("%1 -Tpng %2 -o %3").arg(graphVizPath.toStdString().c_str(),pathToFile.c_str(),pathToImage.c_str());
    qDebug()<<cmdCommand;
    system(cmdCommand.toStdString().c_str());
    QImage image(pathToImage.c_str());

    return image;
}

template<typename K, typename V>
void Drawer<K,V>::setPathToGraphvizDotFile(QString graphVizPath)
{
    this->graphVizPath = graphVizPath;
}
#endif // DRAWER_H
