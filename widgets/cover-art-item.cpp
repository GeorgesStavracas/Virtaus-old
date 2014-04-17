#include "cover-art-item.h"

CoverArtItem::CoverArtItem(QGraphicsItem *parent)
   : QObject(), QGraphicsItem(parent)
{
    this->c_selected = false;
    this->c_last = false;
    this->c_right= false;
    this->standardItem = NULL;
}

CoverArtItem::~CoverArtItem()
{
}

QRectF
CoverArtItem::boundingRect() const
{
    return QRectF(0, 0, size().width(), size().height());
}


void
CoverArtItem::setPos(qreal x, qreal y)
{
    if (c_right)
    {
        setX(x + size().width());
        setY(y + size().height());
    }

    else
    {
        setX(x);
        setY(y);
    }
}

void
CoverArtItem::setYRotation(qreal rot) {
    QTransform tran;
    tran.translate(0, size().height()/2);

    tran.translate(c_origin.x(), 0);
    tran.rotate(rot, Qt::YAxis);
    tran.translate(-c_origin.x(), 0);

    tran.translate(0, -size().height()/2);
    setTransform(tran);
    c_rot = rot;
}

void
CoverArtItem::setOrigin(QPointF point)
{
    c_origin.setX(point.x());
    c_origin.setY(point.y());
}

QPointF
CoverArtItem::pos() const
{
    return QPointF(this->x(), this->y());
}

void
CoverArtItem::setItem(QStandardItem* item)
{
    standardItem = item;
}

void
CoverArtItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setOpacity(1.0);

    if (c_selected && !c_last)
        painter->fillRect(QRectF(0, 0, size().width(), size().height()), Qt::darkGray);
    else
        painter->fillRect(QRectF(0, 0, size().width(), size().height()), Qt::white);

    painter->setPen(Qt::darkGray);
    painter->drawRect(QRectF(0, 0, size().width(), size().height()));


    if (this->standardItem)
    {
        QIcon icon = standardItem->icon();
        QPixmap pix = icon.pixmap(QSize(size().width(), size().height()));
        painter->drawPixmap(boundingRect(), pix, pix.rect());

        int rect_height = ceil(size().height()/6);


        if (!c_last)
        {
            painter->setOpacity(0.66);
            painter->fillRect(QRectF(0, 5*rect_height, size().width(), rect_height), QBrush(Qt::black));
            painter->setOpacity(1.0);
        }


        painter->setPen(Qt::white);
        painter->setFont(QFont("Arial", 16, QFont::Light));

        painter->drawText(QRect(0, 5*rect_height, size().width(),rect_height),
                            Qt::AlignCenter , standardItem->text());
    }


}

