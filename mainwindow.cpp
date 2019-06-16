#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>

CoreFacade<int,int>*core = new CoreFacade<int,int>;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //core = new CoreFacade;
    //ui->view2->setFocus();
    ui->view1->installEventFilter(this);
    ui->view2->installEventFilter(this);

    currentStructureIndex = 1;
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
            currentStructureIndex = 1;
        }
        else if (v == ui->view2)
        {
            ui->view2->setStyleSheet("QGraphicsView { border: 2px solid red }");
            currentStructureIndex = 2;
        }
    }
    if(event->type() == QEvent::FocusOut)
    {
        QGraphicsView*v = dynamic_cast<QGraphicsView*>(object);
        if (v == ui->view1)
        {
            ui->view1->setStyleSheet("QGraphicsView { border: none }");
        }
        else if (v == ui->view2)
        {
            ui->view2->setStyleSheet("QGraphicsView { border: none }");
        }

    }
    return QObject::eventFilter(object, event);

}

void MainWindow::on_insertBTN_clicked()
{    
    int key = QInputDialog::getInt(this,"Enter Key","Enter Key");
    int value = QInputDialog::getInt(this,"Enter Value","Enter Value");
    QGraphicsView*view;
    if(currentStructureIndex == 1)
    {
        view = ui->view1;
    }
    else {
        view = ui->view2;
    }
    core->insert(key,value,currentStructureIndex);
    core->drawStructure(currentStructureIndex,view);
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

}

void MainWindow::on_intersectionBTN_clicked()
{

}

void MainWindow::on_symDiffBTN_clicked()
{

}

void MainWindow::on_diffBTN_clicked()
{

}
