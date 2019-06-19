#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "corefacade.h"
#include <QWheelEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow()override;

    bool eventFilter(QObject *object, QEvent *event)override;

    void Insert(const QString &key, const QString &value);

    void wheelEvent(QWheelEvent *event)override;

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

    void on_clearBTN_clicked();

    void changeStructure();

    void on_actionSet_path_to_graphviz_triggered();

    void on_sortValues_clicked();

private:
    Ui::MainWindow *ui;
    int currentStructureIndex;
    QDialog *insertWindow;
    CoreFacade<int,int>*core;
    int scaleIndex;
    qreal h11,h22,h12,h21;
};

#endif // MAINWINDOW_H
