#ifndef COVERARTWIDGET_H
#define COVERARTWIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QTransform>
#include <QRegion>
#include <QtCore>
#include <QtGui>
#include "widgets/cover-art-item.h"
#include "widgets/cover-art-scene.h"

namespace Ui {
class CoverArtWidget;
}

class CoverArtWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CoverArtWidget(QWidget *parent = 0);
    ~CoverArtWidget();

    void setModel (QStandardItemModel *list);

    QStandardItemModel* getModel();

protected slots:
    void selection_changed(int index);
    void animationFinished();

signals:
    void indexChanged(int index);
    void indexRemove(int index);


protected:
    void resizeEvent(QResizeEvent* event);
    void slideTo(int index);

private:
    void place_widgets();

    Ui::CoverArtWidget *ui;
    CoverArtScene* scene;
    QList<CoverArtItem*>* itemList;

    int speed;
    int stack_move;
    int center_padding;

    QStandardItemModel *model;
};

#endif // COVERARTWIDGET_H
