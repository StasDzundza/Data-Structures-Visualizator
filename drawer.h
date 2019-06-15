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

using std::string;
using std::map;

template<typename K,typename V>
class Drawer
{
public:
    Drawer();

    QImage createPngImage(StructureRepresentor<K,V>*s,QGraphicsView*view);
private:
    map<int,std::string> path;
};

template<typename K,typename V>
Drawer<K,V>::Drawer()
{
    //typedef typename StructureRepresentor<K,V>::Type Type;
    path = {{0,"Output\\SplayTree\\"},{1,"Output\\RedBlack\\"},{2,"Output\\LinkedList\\"},{3,"Output\\StlList\\"}};

}

template<typename K,typename V>
QImage Drawer<K,V>::createPngImage(StructureRepresentor<K,V> *s,QGraphicsView*view)
{
    string pathToFile = path[s->getType()];
    string pathToImage = pathToFile;
    pathToFile+="structure.dot";
    pathToFile+="structure.png";
    s->writeDotFile(pathToFile.c_str());
    string dotFile = "..\\exam\\" + pathToFile;
    string commanStr = "";
    commanStr += "..\\exam\\graphviz\\bin\\dot.exe -Tpng " + dotFile + " -o structure.png";
    system(commanStr.c_str());
    QImage image(pathToImage.c_str());

    QGraphicsPixmapItem *item = new QGraphicsPixmapItem( QPixmap::fromImage( image ) );
    QGraphicsScene* scene = new QGraphicsScene;
    view->setScene( scene);
    view->fitInView(image.rect(),Qt::KeepAspectRatio);
    //view->scale()

    scene->addItem( item );
    item->setPos( 0, 0 );
}
#endif // DRAWER_H
