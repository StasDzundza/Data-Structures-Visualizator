#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include "insertdialog.h"
#include <QGraphicsSceneWheelEvent>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->view1->installEventFilter(this);
    ui->view2->installEventFilter(this);

    currentStructureIndex = 1;

    insertWindow = new InsertDialog(this);

    core = new CoreFacade<int,int>(ui->view1,ui->view2,ui->statusBar);

    connect(ui->actionStlMap, &QAction::triggered, this, &MainWindow::changeStructure);
    connect(ui->actionStlList_2, &QAction::triggered, this, &MainWindow::changeStructure);
    connect(ui->actionStlVector, &QAction::triggered, this, &MainWindow::changeStructure);
    connect(ui->actionForward_list, &QAction::triggered, this, &MainWindow::changeStructure);
    connect(ui->actionSplayTree, &QAction::triggered, this, &MainWindow::changeStructure);
    connect(ui->actionRedBlack_Tree, &QAction::triggered, this, &MainWindow::changeStructure);

    ui->firstTypeLbl->setText("CustomList");
    ui->secondTypeLbl->setText("CustomList");

    ui->firstTypeLbl->setEnabled(false);
    ui->secondTypeLbl->setEnabled(false);

    scaleIndex = 1;

    h11 = 1.0;
    h12 = 0  ;
    h21 = 1.0;
    h22 = 0  ;
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    QGraphicsView*view;
    (currentStructureIndex==1)?view = ui->view1:view=ui->view2;
    view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    // Scale the view / do the zoom
    double scaleFactor = 1.15;
    if(event->delta() > 0) {
        // Zoom in
        view-> scale(scaleFactor, scaleFactor);

    } else {
        // Zooming out
         view->scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
        event->accept();
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
    int key = QInputDialog::getInt(this,"Get key","Enter key");
    int value = QInputDialog::getInt(this,"Get value","Enter value");
    core->insert(key,value,currentStructureIndex);
    core->drawStructure(currentStructureIndex);
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
    core->remove(key,currentStructureIndex);
    core->drawStructure(currentStructureIndex);
}

void MainWindow::on_findBTN_clicked()
{
    int key = QInputDialog::getInt(this,"Key","Enter Key");

    auto value = core->find(currentStructureIndex,key);

    QString message = "Value with key " + QString::number(key) + " is " + QString::number(value);
    QMessageBox::information(this,"Find result",message);
}

void MainWindow::on_randomInsertBTN_clicked()
{
    int amount = QInputDialog::getInt(this,"Amount","Enter amount");
    core->randomInsert(currentStructureIndex,amount);
}

void MainWindow::on_getListBTN_clicked()
{
    core->getKeys(currentStructureIndex);
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

void MainWindow::on_clearBTN_clicked()
{
    core->clear(currentStructureIndex);
}

void MainWindow::changeStructure()
{
    QObject *object = sender();
    QAction *action = qobject_cast<QAction*>(object);
    core->changeStructure(currentStructureIndex,action->iconText());
    (currentStructureIndex==1)?ui->firstTypeLbl->setText(action->iconText()):ui->secondTypeLbl->setText(action->iconText());
    if(action->iconText()=="Custom List" || action->iconText()=="StlList")
        ui->sortBTN->setVisible(true);
    else
        ui->sortBTN->setVisible(false);
}

