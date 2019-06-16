#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "corefacade.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool eventFilter(QObject *object, QEvent *event)override;

private slots:
    void on_insertBTN_clicked();

    void on_removeBTN_clicked();

    void on_findBTN_clicked();

    void on_randomInsertBTN_clicked();

    void on_getListBTN_clicked();

    void on_union_2_clicked();

    void on_intersectionBTN_clicked();

    void on_symDiffBTN_clicked();

    void on_diffBTN_clicked();

    void on_sortBTN_clicked();

private:
    Ui::MainWindow *ui;
    //CoreFacade*core;
    int currentStructureIndex;
};

#endif // MAINWINDOW_H
