#ifndef DIAGRAMROW_H
#define DIAGRAMROW_H

#include <QWidget>
#include "core/collection.h"

namespace Ui {
class DiagramRow;
}

class DiagramRow : public QWidget
{
    Q_OBJECT

public:
    explicit DiagramRow(QWidget *parent = 0);
    ~DiagramRow();

    void setCategory (Virtaus::Category* category);
    void setSelectable (bool selectable);

    bool isSelectable();

protected:
    Virtaus::Category* current;
    QStandardItemModel* model;
    bool selectable;

private:
    Ui::DiagramRow *ui;
};

#endif // DIAGRAMROW_H
