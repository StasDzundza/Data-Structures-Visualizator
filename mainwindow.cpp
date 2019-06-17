#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <osrbtree.h>
#include "insertdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //core = new CoreFacade;

    ui->view1->installEventFilter(this);
    ui->view2->installEventFilter(this);

    currentStructureIndex = 1;

    insertWindow = new InsertDialog(this);

    core = new CoreFacade<int,int>;
}


MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::FocusIn)
    {
        QGraphicsView*v = dynamic_cast<QGraphicsView*>(object);
        if (v == ui->view1)
        {
            ui->view1->setStyleSheet("QGraphicsView { border: 2px solid red }");
            ui->view2->setStyleSheet("QGraphicsView { border: none }");
            currentStructureIndex = 1;
        }
        else if (v == ui->view2)
        {
            ui->view2->setStyleSheet("QGraphicsView { border: 2px solid red }");
            ui->view1->setStyleSheet("QGraphicsView { border: none }");
            currentStructureIndex = 2;
        }
    }

    return QObject::eventFilter(object, event);
}

void MainWindow::on_insertBTN_clicked()
{
    //insertWindow->open();
    QGraphicsView*view;
    if(currentStructureIndex == 1)
    {
        view = ui->view1;
    }
    else {
        view = ui->view2;
    }
    int key = QInputDialog::getInt(this,"Get key","Enter key");
    int value = QInputDialog::getInt(this,"Get value","Enter value");
    core->insert(key,value,currentStructureIndex);
    core->drawStructure(currentStructureIndex,view);

}

void MainWindow::Insert(const QString &key, const QString &value)
{
    //QGraphicsView*view;
    //if(currentStructureIndex == 1)
    //{
    //    view = ui->view1;
    //}
    //else {
    //    view = ui->view2;
    //}
    //core->insert(key.toInt(),value.toInt(),currentStructureIndex);
    //core->drawStructure(currentStructureIndex,view);
}

void MainWindow::on_removeBTN_clicked()
{
    int key = QInputDialog::getInt(this,"Enter Key","Enter Key");
    QGraphicsView*view;
    if(currentStructureIndex == 1)
    {
        view = ui->view1;
    }
    else {
        view = ui->view2;
    }
    core->remove(key,currentStructureIndex);
    core->drawStructure(currentStructureIndex,view);
}

void MainWindow::on_findBTN_clicked()
{
    int key = QInputDialog::getInt(this,"Enter Key","Enter Key");

    auto value = core->find(key);

    QString message = "Value with key " + QString::number(key) + " is " + value;
    QMessageBox::information(this,"Find result",message);
}

void MainWindow::on_randomInsertBTN_clicked()
{

}

void MainWindow::on_getListBTN_clicked()
{

}

void MainWindow::on_union_2_clicked()
{
    core->Union();
}

void MainWindow::on_intersectionBTN_clicked()
{
    core->Intersection();
}

void MainWindow::on_symDiffBTN_clicked()
{
    core->SymDiff();
}

void MainWindow::on_diffBTN_clicked()
{
    core->Diff();
}

void MainWindow::on_sortBTN_clicked()
{

}


