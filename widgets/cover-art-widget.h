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

    Q_PROPERTY(bool antialiasing READ antialiasing WRITE setAntialiasing)
    Q_PROPERTY(bool smoothpixel READ smoothpixel WRITE setSmoothpixel)
    Q_PROPERTY(bool disableEffectOnAnimation READ disableEffectOnAnimation WRITE setDisableEffectOnAnimation)

public:
    explicit CoverArtWidget(QWidget *parent = 0);
    ~CoverArtWidget();

    void setModel (QStandardItemModel *list);

    void setAntialiasing(bool value)
    {
        setRenderHint(QPainter::Antialiasing, value);
        c_antialiasing = value;
    }

    void setSmoothpixel(bool value)
    {
        setRenderHint(QPainter::SmoothPixmapTransform, value);
        c_smoothpixel = value;
    }

    void setDisableEffectOnAnimation(bool value){c_disableeffects = value;}

    bool antialiasing() const {return c_antialiasing;}
    bool disableEffectOnAnimation() const {return c_disableeffects;}
    bool smoothpixel() const {return c_smoothpixel;}

    QStandardItemModel* getModel();

protected slots:
    void selection_changed(int index);
    void animationFinished();

signals:
    void indexChanged(int index);
    void indexRemove(int index);

protected:
    void setRenderHint(QPainter::RenderHint r, bool value);
    void resizeEvent(QResizeEvent* event);
    void slideTo(int index);

private:
    void place_widgets();

    Ui::CoverArtWidget *ui;
    CoverArtScene* scene;
    QList<CoverArtItem*>* itemList;

    bool c_antialiasing;
    bool c_smoothpixel;
    bool c_disableeffects;

    int speed;
    int stack_move;
    int center_padding;

    QStandardItemModel *model;
};

#endif // COVERARTWIDGET_H
