#ifndef CATEGORYVIEW_H
#define CATEGORYVIEW_H

#include <QWidget>
#include "virtaus-application.h"

namespace Ui {
class CategoryView;
}

class CategoryView : public QWidget
{
    Q_OBJECT

public:
    explicit CategoryView(QWidget *parent = 0);
    ~CategoryView();

protected slots:
    void sets_view();

private:
    Ui::CategoryView *ui;
};

#endif // CATEGORYVIEW_H
