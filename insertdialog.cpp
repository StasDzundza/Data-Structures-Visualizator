#include "insertdialog.h"
#include "ui_insertdialog.h"
#include "mainwindow.h"

InsertDialog::InsertDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InsertDialog)
{
    ui->setupUi(this);
    connect(ui->okBTN, &QPushButton::clicked, this, &InsertDialog::on_okBTN_clicked);
}

InsertDialog::~InsertDialog()
{
    delete ui;
}

void InsertDialog::on_okBTN_clicked()
{
    QString key = ui->keyLine->text();
    QString value = ui->valueLine->text();

    MainWindow *w = qobject_cast<MainWindow*>(parent());
    w->Insert(key,value);

    this->hide();
}
