#include "image-graphic-item.h"

ImageGraphicItem::ImageGraphicItem() :
    QGraphicsItem()
{
    this->middle = false;
    this->position = -1;
}


QRectF
ImageGraphicItem::boundingRect() const
{
    QRectF rect(0,0,100,100);

    return rect;
}

void
ImageGraphicItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QRectF rect = boundingRect();

    painter->setPen(QPen(Qt::blue, 2));
    painter->drawRoundedRect(rect, 2, 2);
}
