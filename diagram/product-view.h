#ifndef PRODUCTVIEW_H
#define PRODUCTVIEW_H

#include <QWidget>
#include "core/collection.h"

namespace Ui {
class ProductView;
}

class ProductView : public QWidget
{
    Q_OBJECT

public:
    explicit ProductView(QWidget *parent = 0);
    ~ProductView();

    void setCollection (Virtaus::Collection* collection);

protected slots:
    void show_diagram_view();
    void show_info_view();
    void show_product_view();

private:
    Ui::ProductView *ui;
};

#endif // PRODUCTVIEW_H
