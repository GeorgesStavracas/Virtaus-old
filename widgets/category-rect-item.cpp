#include "category-rect-item.h"

CategoryRectItem::CategoryRectItem(QGraphicsItem *parent) :
    QObject(), QGraphicsRectItem(parent)
{
    c_selected = false;

    base_color = QColor(255, 255, 255);

    // Init random generator seed
    qsrand((uint) QTime::currentTime().msec());

    int red = rand() % 256;
    int green = rand() % 256;
    int blue = rand() % 256;

    rect_color = QColor((red + base_color.red())/2,
                (green + base_color.green())/2,
                (blue + base_color.blue())/2);
}

void
CategoryRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::black);
    painter->setOpacity(0.75);
    painter->drawRect(boundingRect());

    painter->setOpacity(0.5);
    painter->setPen(rect_color);
    painter->fillRect(boundingRect(), QBrush(rect_color));

    if(c_selected)
    {
        painter->setOpacity(0.25);
        painter->setPen(Qt::black);
        painter->fillRect(boundingRect(), QBrush(Qt::black));
    }
}
