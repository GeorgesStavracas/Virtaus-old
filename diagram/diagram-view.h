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

    void setCollection (Virtaus::Collection* collection);

signals:
    void itemEdit(Virtaus::Item* item);
    void itemSelected (Virtaus::Item* item);

public slots:


protected:
    Virtaus::Collection* current;
};

#endif // DIAGRAMVIEW_H
