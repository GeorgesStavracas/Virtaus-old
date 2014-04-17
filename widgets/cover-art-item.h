#ifndef COVERARTITEM_H
#define COVERARTITEM_H

#include <QGraphicsItem>
#include <QtWidgets>
#include <QPainter>
#include <QPropertyAnimation>
#include <QTimerEvent>
#include <QTimer>
#include <QDebug>

class CoverArtItem : public QObject, public QGraphicsItem
{
    Q_OBJECT

    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    Q_PROPERTY(QSizeF size READ size WRITE setSize)
    Q_PROPERTY(qreal yrotation READ yrotation WRITE setYRotation)
    Q_PROPERTY(int index READ index WRITE setIndex)
    Q_PROPERTY(bool selected READ selected WRITE setSelected)
    Q_PROPERTY(QStandardItem* item READ item WRITE setItem)
    Q_PROPERTY(bool isLast READ isLast WRITE setIsLast)
    Q_PROPERTY(QPointF origin READ origin WRITE setOrigin)

public:
    explicit CoverArtItem(QGraphicsItem *parent = 0);
    ~CoverArtItem();

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /* Properties */
    void setPos(qreal x, qreal y);
    void setPos(QPointF & p) {setX(p.x()); setY(p.y());}
    void setSize(qreal w, qreal h) {c_size.setWidth(w); c_size.setHeight(h);}
    void setSize(QSizeF & s) {c_size.setWidth(s.width()); c_size.setHeight(s.height());}
    void setIndex(int index) {c_index = index;}
    void setSelected(bool selected){ c_selected = selected;}
    void setIsLast(bool isLast) {c_last = isLast;}
    void setOrigin(QPointF point);

    void setYRotation(qreal rot);
    void setItem(QStandardItem* item);

    bool selected() const { return c_selected; }
    int index() const { return c_index; }
    QPointF pos() const;
    qreal yrotation() const {return c_rot;}
    QSizeF size() const { return c_size; }
    QStandardItem* item() const {return standardItem;}
    bool isLast() const {return c_last;}
    QPointF origin() const {return c_origin;}

private:
    QSizeF c_size;
    QPointF c_origin;
    bool c_selected;
    bool c_right;
    bool c_last;
    int c_index;
    int c_rot;

    QStandardItem* standardItem;
};

#endif // COVERARTITEM_H
