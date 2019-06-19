#ifndef COREFACADE_H
#define COREFACADE_H

#include <QGraphicsView>
#include "drawer.h"
#include <fstream>
#include "setoperationsview.h"
#include "structurefactory.h"
#include "randomgenerator.h"
#include <QStatusBar>
#include <chrono>
#include <QDebug>
#include <QFileDialog>
#include <QObject>
#include <QWidget>
#include <QMessageBox>

using std::vector;

template <typename K,typename V>
class StructureRepresentor;

template <typename K,typename V>
class CoreFacade
{
public:
    CoreFacade();

    CoreFacade(QGraphicsView*v1,QGraphicsView*v2,QStatusBar*bar,QWidget*parent);

    ~CoreFacade();

    void insert(const K& key,const V& value,const int& structureIndex);

    void remove(const K& key,const int& structureIndex);

    void drawStructure(const int& struct_index);

    void drawStructure(StructureRepresentor<K,V>*s,QGraphicsView*view);

    void randomInsert(const int& struct_index,const int& amount);

    V find(const int& structure_index,const K& key);

    void Union(const int& struct_index);

    void Intersection(const int& struct_index);

    void SymDiff(const int& struct_index);

    void Diff(const int& struct_index);

    void getKeys(const int& structure_index);

    void sortByValue(const int& struct_index);

    void sortByKey(const int& struct_index);

    void clear(const int& struct_index);

    void changeStructure(const int& struct_index,const QString &iconText);

    void setTimePassed(const QString&time);

    void setPathToGraphvizDotFile();

private:
    StructureRepresentor<K,V>*s1,*s2;

    StructureRepresentor<K,V>*getStructureFromIndex(int struct_index);

    QGraphicsView *getViewFromIndex(int view_index);

    Drawer<K,V>*drawer;

    SetOperationsView*sView = nullptr;

    StructureFactory*factory;

    QGraphicsView*view1;

    QGraphicsView*view2;

    QStatusBar*mw_bar;

    RandomGenerator<K,V>*random;

    QWidget*parent;
};

template <typename K,typename V>
CoreFacade<K,V>::CoreFacade()
{
    s1 = new List<int,int>();
    s2 = new List<int,int>();

    drawer = new Drawer<K,V>();

    sView = new SetOperationsView;

    factory = StructureFactory::getInstance();

    random = new RandomGenerator<K,V>;

}

template <typename K,typename V>
CoreFacade<K,V>::CoreFacade(QGraphicsView*v1,QGraphicsView*v2,QStatusBar*bar,QWidget*parent):CoreFacade<K,V>()
{
    view1 = v1;
    view2 = v2;
    mw_bar = bar;
    this->parent = parent;

    QFile file("GraphViz_Path.txt");
    if(!file.exists())
    {
        QMessageBox::warning(parent,"Enter Path To GraphViz","You should choose path to graphviz dot.exe file. It should be in graphviz\\bin\\ folder.");
        this->setPathToGraphvizDotFile();
    }
    else if((file.open(QIODevice::ReadOnly)))
    {
        QString str="";
        while(!file.atEnd())
        {
            str+=file.readLine();
        }
        file.close();
        drawer->setPathToGraphvizDotFile(str);
    }
}

template<typename K, typename V>
CoreFacade<K,V>::~CoreFacade()
{
    delete s1,s2;
    delete factory,drawer,sView,random;
}

template <typename K,typename V>
void CoreFacade<K,V>::insert(const K& key,const V& value,const int& struct_index)
{
    StructureRepresentor<K,V>*s = getStructureFromIndex(struct_index);
    auto begin = std::chrono::steady_clock::now();
    s->insert(key,value);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    setTimePassed(QString::number(elapsed_ms.count()));
}

template<typename K, typename V>
void CoreFacade<K,V>::remove(const K& key,const int& structureIndex)
{
    StructureRepresentor<K,V>*s = getStructureFromIndex(structureIndex);
    auto begin = std::chrono::steady_clock::now();
    s->remove(key);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    setTimePassed(QString::number(elapsed_ms.count()));
}

template <typename K,typename V>
void CoreFacade<K,V>::drawStructure(const int& struct_index)
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
void CoreFacade<K,V>::randomInsert(const int& struct_index,const int& amount)
{
    StructureRepresentor<K,V>*s = getStructureFromIndex(struct_index);
    if(s->isEmpty())
    {
        auto begin = std::chrono::steady_clock::now();
        random->fillStructureInt(s,amount);
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        setTimePassed(QString::number(elapsed_ms.count()));
        drawStructure(struct_index);
    }
    else {
        mw_bar->showMessage("Structure should be empty for random filling");
    }
}

template<typename K, typename V>
V CoreFacade<K,V>::find(const int& structure_index,const K& key)
{
    StructureRepresentor<K,V>*s = getStructureFromIndex(structure_index);
    auto begin = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    setTimePassed(QString::number(elapsed_ms.count()));
    return s->find(key);
}

template<typename K, typename V>
void CoreFacade<K,V>::Union(const int& struct_index)
{
   auto begin = std::chrono::steady_clock::now();
   StructureRepresentor<K, V>*U = (struct_index==1)?s1->Union(s2):s2->Union(s1);
   auto end = std::chrono::steady_clock::now();
   auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
   setTimePassed(QString::number(elapsed_ms.count()));
   if(!U->isEmpty())
   drawStructure(U,sView->getView());
   delete U;
}

template<typename K, typename V>
void CoreFacade<K,V>::Intersection(const int& struct_index)
{
    auto begin = std::chrono::steady_clock::now();
    StructureRepresentor<K, V>*I = (struct_index==1)?s1->Intersection(s2):s2->Intersection(s1);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    setTimePassed(QString::number(elapsed_ms.count()));
    if(!I->isEmpty())
    drawStructure(I,sView->getView());
    delete I;
}

template<typename K, typename V>
void CoreFacade<K,V>::SymDiff(const int& struct_index)
{
    auto begin = std::chrono::steady_clock::now();
    StructureRepresentor<K, V>*SD = (struct_index==1)?s1->SymDiff(s2):s2->SymDiff(s1);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    setTimePassed(QString::number(elapsed_ms.count()));
    if(!SD->isEmpty())
    drawStructure(SD,sView->getView());
    delete SD;
}

template<typename K, typename V>
void CoreFacade<K,V>::Diff(const int& struct_index)
{
    auto begin = std::chrono::steady_clock::now();
    StructureRepresentor<K, V>*D = (struct_index==1)?s1->Diff(s2):s2->Diff(s1);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    setTimePassed(QString::number(elapsed_ms.count()));
    if(!D->isEmpty())
    drawStructure(D,sView->getView());
    delete D;
}

template<typename K, typename V>
void CoreFacade<K,V>::getKeys(const int& structure_index)
{
    StructureRepresentor<K, V>*keys = new StlList<K,V>;
    StructureRepresentor<K,V>*s = getStructureFromIndex(structure_index);
    auto begin = std::chrono::steady_clock::now();
    vector<pair<K,V>>key_val = s->getKeys();
    for(pair<K,V>p:key_val)
        keys->insert(p.first,p.second);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    setTimePassed(QString::number(elapsed_ms.count()));
    drawStructure(keys,sView->getView());
}

template<typename K, typename V>
void CoreFacade<K,V>::sortByKey(const int& struct_index)
{
    StructureRepresentor<K,V>*s = getStructureFromIndex(struct_index);
    auto begin = std::chrono::steady_clock::now();
    s->sortByKey();
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    setTimePassed(QString::number(elapsed_ms.count()));
    drawStructure(struct_index);
}

template<typename K, typename V>
void CoreFacade<K,V>::sortByValue(const int& struct_index)
{
    StructureRepresentor<K,V>*s = getStructureFromIndex(struct_index);
    auto begin = std::chrono::steady_clock::now();
    s->sortByValue();
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    setTimePassed(QString::number(elapsed_ms.count()));
    drawStructure(struct_index);
}

template<typename K, typename V>
void CoreFacade<K,V>::clear(const int& struct_index)
{
    StructureRepresentor<K,V>*s = getStructureFromIndex(struct_index);
    auto begin = std::chrono::steady_clock::now();
    s->clear();
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    setTimePassed(QString::number(elapsed_ms.count()));
    QGraphicsView*view = getViewFromIndex(struct_index);
    if(view->scene()!=nullptr)
    {
        view->scene()->clear();
        view->scene()->deleteLater();
    }
}

template<typename K, typename V>
void CoreFacade<K,V>::changeStructure(const int& struct_index,const QString &iconText)
{
    clear(struct_index);
    if(struct_index == 1)
    {
        delete s1;
        s1 = factory->createStructure(iconText);
    }
    else {
        delete s2;
        s2 = factory->createStructure(iconText);
    }
}

template<typename K, typename V>
void CoreFacade<K,V>::setTimePassed(const QString &time)
{
    mw_bar->showMessage("Time Passed " + time + " nanoseconds.");
}

template<typename K, typename V>
void CoreFacade<K,V>::setPathToGraphvizDotFile()
{
    QString path = QFileDialog::getOpenFileName(parent,QObject::tr("Open dot.exe file"),
                                                            "/home",
                                                            QObject::tr("Images (*.exe)"));

    drawer->setPathToGraphvizDotFile(path);

    QFile fileOut("GraphViz_Path.txt");
    fileOut.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream writeStream(&fileOut);
    writeStream << path;
    fileOut.close();
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
