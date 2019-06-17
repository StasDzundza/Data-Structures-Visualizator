#include "setoperationsview.h"
#include "ui_setoperationsview.h"

SetOperationsView::SetOperationsView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetOperationsView)
{
    ui->setupUi(this);
}

SetOperationsView::~SetOperationsView()
{
    delete ui;
}

QGraphicsView *SetOperationsView::getView()
{
    return ui->graphicsView;
}
