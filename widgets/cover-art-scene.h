#ifndef COVERARTSCENE_H
#define COVERARTSCENE_H

#include <QGraphicsScene>
#include "widgets/cover-art-item.h"

class CoverArtScene : public QGraphicsScene
{
    Q_OBJECT

    Q_PROPERTY(qreal scrollSpeed READ scrollSpeed WRITE setScrollSpeed)
    Q_PROPERTY(int currentItem READ currentItem WRITE setCurrentItem NOTIFY itemSelected)

public:
    CoverArtScene();

    void setScrollSpeed(qreal speed) {scroll_speed = speed;}
    void setCurrentItem(int item) {current_item = item;}

    qreal scrollSpeed() const {return scroll_speed;}
    int currentItem() const {return current_item;}

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);

    int clicked_item;
    int current_item;
    qreal scroll_speed;


signals:
    void itemSelected(int index);
    void itemEdit(int index);
};

#endif // COVERARTSCENE_H
