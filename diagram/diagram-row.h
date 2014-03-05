#ifndef DIAGRAMROW_H
#define DIAGRAMROW_H

#include <QWidget>

namespace Ui {
class DiagramRow;
}

class DiagramRow : public QWidget
{
    Q_OBJECT

public:
    explicit DiagramRow(QWidget *parent = 0);
    ~DiagramRow();

private:
    Ui::DiagramRow *ui;
};

#endif // DIAGRAMROW_H
