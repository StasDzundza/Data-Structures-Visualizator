#ifndef COREFACADE_H
#define COREFACADE_H

#include <QGraphicsView>
#include "drawer.h"
#include <fstream>

template <typename K,typename V>
class StructureRepresentor;

template <typename K,typename V>
class CoreFacade
{
public:
    CoreFacade();
    void insert(K key,V value, int structureIndex);

    void drawStructure(int struct_index,QGraphicsView *view);

private:
    StructureRepresentor<K,V>*s1,*s2;

    StructureRepresentor<K,V>*getStructureFromIndex(int struct_index);

    Drawer<K,V>*drawer;
};

template <typename K,typename V>
CoreFacade<K,V>::CoreFacade()
{
    s1 = new StlList<int,int>();
    s2 = new StlList<int,int>();
    drawer = new Drawer<K,V>();
}

template <typename K,typename V>
void CoreFacade<K,V>::insert(K key, V value, int struct_index)
{
    StructureRepresentor<K,V>*s = getStructureFromIndex(struct_index);
    s->insert(key,value);
}

template <typename K,typename V>
void CoreFacade<K,V>::drawStructure(int struct_index, QGraphicsView *view)
{
    StructureRepresentor<K,V>*s = getStructureFromIndex(struct_index);
    QImage image = drawer->createPngImage(s);
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem( QPixmap::fromImage( image ) );
    QGraphicsScene* scene;
    if(view->scene()==nullptr)
    {
        scene = new QGraphicsScene;
    }
    else
    {
        scene = view->scene();
    }
    view->setScene(scene);
    view->fitInView(image.rect(),Qt::KeepAspectRatio);
    scene->addItem( item );
    item->setPos( 0, 0 );


}

template <typename K,typename V>
StructureRepresentor<K,V> *CoreFacade<K,V>::getStructureFromIndex(int struct_index)
{
    StructureRepresentor<K,V>*s = nullptr;
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
#endif // COREFACADE_H
