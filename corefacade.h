#ifndef COREFACADE_H
#define COREFACADE_H

#include <QGraphicsView>
#include "drawer.h"
#include <fstream>
#include <vector>
#include "setoperationsview.h"

using std::vector;

template <typename K,typename V>
class StructureRepresentor;

template <typename K,typename V>
class CoreFacade
{
public:
    CoreFacade();

    void insert(K key,V value, int structureIndex);

    bool remove(K key, int structureIndex);

    void drawStructure(int struct_index,QGraphicsView *view);

    void drawStructure(StructureRepresentor<K,V>*s,QGraphicsView *view);

    void randomInsert();

    V find(K key);

    void Union();

    void Intersection();

    void SymDiff();

    void Diff();

    vector<K> getKeys();

    void sort();

    void clear();


private:
    StructureRepresentor<K,V>*s1,*s2;

    StructureRepresentor<K,V>*getStructureFromIndex(int struct_index);

    Drawer<K,V>*drawer;

    SetOperationsView*sView = nullptr;
};

template <typename K,typename V>
CoreFacade<K,V>::CoreFacade()
{
    s1 = new List<int,int>();
    s2 = new List<int,int>();
    drawer = new Drawer<K,V>();

    sView = new SetOperationsView;
}

template <typename K,typename V>
void CoreFacade<K,V>::insert(K key, V value, int struct_index)
{
    StructureRepresentor<K,V>*s = getStructureFromIndex(struct_index);
    s->insert(key,value);
}

template<typename K, typename V>
bool CoreFacade<K,V>::remove(K key, int structureIndex)
{
    StructureRepresentor<K,V>*s = getStructureFromIndex(structureIndex);
    s->remove(key);
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
        scene->removeItem(scene->items().at(0));
    }
    view->setScene(scene);
    view->fitInView(image.rect(),Qt::KeepAspectRatio);
    scene->addItem( item );
    item->setPos( 0, 0 );
}

template<typename K, typename V>
void CoreFacade<K,V>::drawStructure(StructureRepresentor<K, V> *s, QGraphicsView *view)
{
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
        scene->removeItem(scene->items().at(0));
    }
    view->setScene(scene);
    //view->fitInView(image.rect(),Qt::KeepAspectRatio);
    scene->addItem( item );
    item->setPos( 0, 0 );
    sView->show();
    view->fitInView(image.rect(),Qt::KeepAspectRatio);
}

template<typename K, typename V>
void CoreFacade<K,V>::randomInsert()
{

}

template<typename K, typename V>
V CoreFacade<K,V>::find(K key)
{

}

template<typename K, typename V>
void CoreFacade<K,V>::Union()
{
   StructureRepresentor<K, V>*U = s1->Union(s2);
   drawStructure(U,sView->getView());
}

template<typename K, typename V>
void CoreFacade<K,V>::Intersection()
{
    StructureRepresentor<K, V>*U = s1->Intersection(s2);
    drawStructure(U,sView->getView());
}

template<typename K, typename V>
void CoreFacade<K,V>::SymDiff()
{
    StructureRepresentor<K, V>*U = s1->SymDiff(s2);
    drawStructure(U,sView->getView());
}

template<typename K, typename V>
void CoreFacade<K,V>::Diff()
{
    StructureRepresentor<K, V>*U = s1->Diff(s2);
    drawStructure(U,sView->getView());
}

template<typename K, typename V>
vector<K> CoreFacade<K,V>::getKeys()
{
    //StructureRepresentor<K,V>*s = getStructureFromIndex(struct_index);
    //s->getKeys();
}

template<typename K, typename V>
void CoreFacade<K,V>::sort()
{

}

template<typename K, typename V>
void CoreFacade<K,V>::clear()
{

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
