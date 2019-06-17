#ifndef SETOPERATIONSVIEW_H
#define SETOPERATIONSVIEW_H

#include <QDialog>
#include <QGraphicsView>

namespace Ui {
class SetOperationsView;
}

class SetOperationsView : public QDialog
{
    Q_OBJECT

public:
    explicit SetOperationsView(QWidget *parent = nullptr);
    ~SetOperationsView();
     QGraphicsView* getView();

private:
    Ui::SetOperationsView *ui;
};

#endif // SETOPERATIONSVIEW_H
