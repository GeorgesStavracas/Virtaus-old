#ifndef COVERARTWIDGET_H
#define COVERARTWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QtCore>
#include <QtGui>

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

private:
    Ui::CoverArtWidget *ui;
    QGraphicsScene* scene;
    //QAbstractListModel *model;
};

#endif // COVERARTWIDGET_H
