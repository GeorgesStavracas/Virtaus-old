#ifndef CATEGORYRECTITEM_H
#define CATEGORYRECTITEM_H

#include <QAbstractGraphicsShapeItem>
#include <QtGui>
#include <QtCore>
#include <QColor>

class CategoryRectItem : public QObject, public QGraphicsRectItem
{

    Q_OBJECT

    Q_PROPERTY(bool selected READ selected WRITE setSelected)
    Q_PROPERTY(QColor baseColor READ baseColor WRITE setBaseColor)

public:
    explicit CategoryRectItem(QGraphicsItem *parent = 0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void setSelected(bool selected){c_selected = selected;}
    bool selected() const {return c_selected;}

    void setBaseColor(QColor color){base_color.setRgba(qRgb(color.red(), color.green(), color.blue()));}
    QColor baseColor() const {return base_color;}

private:
    bool c_selected;

    QColor base_color;
    QColor rect_color;

signals:

public slots:

};

#endif // CATEGORYRECTITEM_H
