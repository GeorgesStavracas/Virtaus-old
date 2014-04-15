#ifndef IMAGEGRAPHICITEM_H
#define IMAGEGRAPHICITEM_H

#include <QtWidgets>

class ImageGraphicItem : public QGraphicsItem
{
public:
    explicit ImageGraphicItem();
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:

public slots:

protected:
    bool middle;
    int position;

};

#endif // IMAGEGRAPHICITEM_H
