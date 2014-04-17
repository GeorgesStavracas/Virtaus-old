#ifndef CATEGORYVIEW_H
#define CATEGORYVIEW_H

#include <QWidget>

namespace Ui {
class CategoryView;
}

class CategoryView : public QWidget
{
    Q_OBJECT

public:
    explicit CategoryView(QWidget *parent = 0);
    ~CategoryView();

private:
    Ui::CategoryView *ui;
};

#endif // CATEGORYVIEW_H
