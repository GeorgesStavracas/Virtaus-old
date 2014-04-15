#ifndef COVERARTWIDGET_H
#define COVERARTWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QtCore>
#include <QtGui>
#include "widgets/image-graphic-item.h"

namespace Ui {
class CoverArtWidget;
}

class CoverArtWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CoverArtWidget(QWidget *parent = 0);
    ~CoverArtWidget();

    //void setModel (QAbstractListModel model);

    //QAbstractListModel getModel();

signals:
    void indexChanged(int index);
    void indexRemove(int index);

private:
    void order_widgets();

    Ui::CoverArtWidget *ui;
    QGraphicsScene* scene;
    QList<QGraphicsItem*>* itemList;
    int current;
    //QAbstractListModel *model;
};

#endif // COVERARTWIDGET_H
