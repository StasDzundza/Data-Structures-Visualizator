#include "drawer.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
Drawer::Drawer()
{
    typedef StructureRepresentor::Type Type;
    path = {{(int)Type::SplayTree,"Output\\SplayTree\\"},{(int)Type::BPlus,"Output\\BPlus\\"},{(int)Type::LinkedList,"Output\\LinkedList\\"},{(int)Type::StlList,"Output\\StlList\\"}};

}

QImage Drawer::createPngImage(StructureRepresentor *s,QGraphicsView*view)
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
