#ifndef CATEGORYVIEW_H
#define CATEGORYVIEW_H

#include <QWidget>
#include "virtaus-application.h"
#include "widgets/category-rect-item.h"

namespace Ui {
class CategoryView;
}

class CategoryView : public QWidget
{
    Q_OBJECT

public:
    explicit CategoryView(QWidget *parent = 0);
    ~CategoryView();

protected:
    void resizeEvent(QResizeEvent* event);
    void paintCategories();

protected slots:
    void sets_view();
    void collection_selected(Virtaus::Core::Collection* c);

private:
    Ui::CategoryView *ui;

    QGraphicsScene* scene;
};

#endif // CATEGORYVIEW_H
