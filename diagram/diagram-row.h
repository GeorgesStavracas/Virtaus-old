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

    void setAttribute(Virtaus::Core::Attribute* attribute);
    void setSelectable (bool selectable);

    bool isSelectable();

signals:
    void itemSelected (Virtaus::Core::Item* item);
    void itemEdit (Virtaus::Core::Item* item);

protected slots:
    void item_selected (QModelIndex index);

protected:
    Virtaus::Core::Attribute* current;
    QStandardItemModel* model;
    bool selectable;

private:
    Ui::DiagramRow *ui;
};

#endif // DIAGRAMROW_H
