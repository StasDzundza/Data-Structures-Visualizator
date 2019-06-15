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

private:
    Ui::MainWindow *ui;
    //CoreFacade*core;
    int currentStructureIndex;
};

#endif // MAINWINDOW_H
