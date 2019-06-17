#ifndef COREFACADE_H
#define COREFACADE_H

#include <QGraphicsView>
#include "drawer.h"
#include <fstream>
#include <vector>
#include "setoperationsview.h"
#include "structurefactory.h"

using std::vector;

template <typename K,typename V>
class StructureRepresentor;

template <typename K,typename V>
class CoreFacade
{
public:
    CoreFacade();

    CoreFacade(QGraphicsView*v1,QGraphicsView*v2);

    void insert(K key,V value, int structureIndex);

    bool remove(K key, int structureIndex);

    void drawStructure(int struct_index);

    void drawStructure(StructureRepresentor<K,V>*s,QGraphicsView*view);

    void randomInsert();

    V find(int structure_index,K key);

    void Union();

    void Intersection();

    void SymDiff();

    void Diff();

    void getKeys(int structure_index);

    void sort();

    void clear(int struct_index);

    void changeStructure(const QString &iconText);

private:
    StructureRepresentor<K,V>*s1,*s2;

    StructureRepresentor<K,V>*getStructureFromIndex(int struct_index);

    QGraphicsView *getViewFromIndex(int view_index);

    Drawer<K,V>*drawer;

    SetOperationsView*sView = nullptr;

    StructureFactory*factory;

    QGraphicsView*view1;

    QGraphicsView*view2;
};

template <typename K,typename V>
CoreFacade<K,V>::CoreFacade()
{
    s1 = new List<int,int>();
    s2 = new List<int,int>();

    drawer = new Drawer<K,V>();

    sView = new SetOperationsView;

    factory = StructureFactory::getInstance();
}

template <typename K,typename V>
CoreFacade<K,V>::CoreFacade(QGraphicsView*v1,QGraphicsView*v2):CoreFacade<K,V>()
{
    view1 = v1;
    view2 = v2;
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
void CoreFacade<K,V>::drawStructure(int struct_index)
{
    StructureRepresentor<K,V>*s = getStructureFromIndex(struct_index);
    QGraphicsView*view = getViewFromIndex(struct_index);
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
void CoreFacade<K,V>::drawStructure(StructureRepresentor<K, V> *s,QGraphicsView*view)
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
V CoreFacade<K,V>::find(int structure_index,K key)
{
    StructureRepresentor<K,V>*s = getStructureFromIndex(structure_index);
    return s->find(key);
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
void CoreFacade<K,V>::getKeys(int structure_index)
{
    StructureRepresentor<K, V>*keys = new StlList<K,V>;
    StructureRepresentor<K,V>*s = getStructureFromIndex(structure_index);
    vector<pair<K,V>>key_val = s->getKeys();
    for(pair<K,V>p:key_val)
        keys->insert(p.first,p.second);
    drawStructure(keys,sView->getView());
}

template<typename K, typename V>
void CoreFacade<K,V>::sort()
{

}

template<typename K, typename V>
void CoreFacade<K,V>::clear(int struct_index)
{
    StructureRepresentor<K,V>*s = getStructureFromIndex(struct_index);
    s->clear();
    QGraphicsView*view = getViewFromIndex(struct_index);
    if(view->scene()!=nullptr)
    {
        view->scene()->clear();
        view->scene()->deleteLater();
    }
}

template<typename K, typename V>
void CoreFacade<K,V>::changeStructure(const QString &iconText)
{
    clear(1);
    clear(2);
    delete s1,s2;
    s1 = factory->createStructure(iconText);
    s2 = factory->createStructure(iconText);
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

template<typename K, typename V>
QGraphicsView *CoreFacade<K,V>::getViewFromIndex(int view_index)
{
    QGraphicsView* v = nullptr;
    if(view_index == 1)
    {
        v = view1;
    }
    else
    {
        v = view2;
    }
    return v;
}
#endif // COREFACADE_H
