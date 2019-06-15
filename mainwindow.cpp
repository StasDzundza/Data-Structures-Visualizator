#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //core = new CoreFacade;
    //ui->view2->setFocus();
    ui->view1->installEventFilter(this);
    ui->view2->installEventFilter(this);
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
        }
        else if (v == ui->view2)
        {
            ui->view2->setStyleSheet("QGraphicsView { border: 2px solid red }");
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
        return false;
}

void MainWindow::on_insertBTN_clicked()
{
    CoreFacade<int,int>*core = new CoreFacade<int,int>;
    core->insert(1,1,currentStructureIndex);
    core->drawStructure(currentStructureIndex,ui->view1);
}
