#ifndef INSERTDIALOG_H
#define INSERTDIALOG_H

#include <QDialog>

namespace Ui {
class InsertDialog;
}

class InsertDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InsertDialog(QWidget *parent = nullptr);
    ~InsertDialog();

private slots:
    void on_okBTN_clicked();

private:
    Ui::InsertDialog *ui;
};

#endif // INSERTDIALOG_H
