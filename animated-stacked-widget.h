#ifndef ANIMATEDSTACKEDWIDGET_H
#define ANIMATEDSTACKEDWIDGET_H

#include <QEasingCurve>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QStackedWidget>

/*
 * All credits for the respective author. Took from:
 * http://developer.nokia.com/community/wiki/Extending_QStackedWidget_for_sliding_page_animations_in_Qt
 */

class AnimatedStackedWidget : public QStackedWidget
{
    Q_OBJECT

public:
    AnimatedStackedWidget(QWidget *parent = 0);
    ~AnimatedStackedWidget(void);

    enum t_effect {
        LEFT_RIGHT,
        RIGHT_LEFT,
        AUTOMATIC,
        TOP_BOTTOM,
        BOTTOM_TOP,
        FADE_IN_OUT
    };

signals:
        //! this is used for internal purposes in the class engine
        void animationFinished(void);

protected slots:
        //! this is used for internal purposes in the class engine
        void animationDoneSlot(void);

protected:
        //! this is used for internal purposes in the class engine
        void slideInWgt(QWidget * widget, enum t_effect direction=AUTOMATIC);

        QWidget *m_mainwindow;

        int m_speed;
        enum QEasingCurve::Type m_animationtype;
        bool m_vertical;
        int m_now;
        int m_next;
        bool m_wrap;
        QPoint m_pnow;
        bool m_active;

        QList<QWidget*> blockedPageList;

public slots:
        //! Some basic settings API
        //animation duration in milliseconds
        void setSpeed(int speed);
        //check out the QEasingCurve documentation for different styles
        void setAnimation(enum QEasingCurve::Type animationtype);
        void setVerticalMode(bool vertical=true);

        //wrapping is related to slideInNext/Prev;it defines the behaviour when reaching last/first page
        void setWrap(bool wrap);

        //! The Animation / Page Change API
        void slideInNext();
        void slideInPrev();
        void slideInIdx(int idx, enum t_effect effect = AUTOMATIC);

};

#endif // ANIMATEDSTACKWIDGET_H
