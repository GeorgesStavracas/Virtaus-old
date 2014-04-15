#ifndef DIAGRAMVIEW_H
#define DIAGRAMVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include "core/collection.h"
#include "core/data-reader.h"
#include "diagram/diagram-row.h"

class DiagramView : public QWidget
{
    Q_OBJECT
public:
    explicit DiagramView(QWidget *parent = 0);

    void setCategory (Virtaus::Core::Category* category);

signals:
    void itemEdit(Virtaus::Core::Item* item);
    void itemSelected (Virtaus::Core::Item* item);

protected slots:
    void item_selected();

protected:
    Virtaus::Core::Category* current;
};

#endif // DIAGRAMVIEW_H
