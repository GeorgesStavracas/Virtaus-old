#ifndef DIAGRAMVIEW_H
#define DIAGRAMVIEW_H

#include <QWidget>

namespace Ui {
class DiagramView;
}

class DiagramView : public QWidget
{
    Q_OBJECT

public:
    explicit DiagramView(QWidget *parent = 0);
    ~DiagramView();

private:
    Ui::DiagramView *ui;
};

#endif // DIAGRAMVIEW_H
