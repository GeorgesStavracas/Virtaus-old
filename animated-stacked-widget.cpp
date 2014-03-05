#include "animated-stacked-widget.h"

AnimatedStackedWidget::AnimatedStackedWidget(QWidget *parent) :
    QStackedWidget(parent)
{
    if (parent != 0) {
        m_mainwindow = parent;
    }
    else {
        m_mainwindow = this;
        //qDebug()<<"ATTENTION: untested mainwindow case !";
    }
    //parent should not be 0; at least not tested for any other case yet !!

    //Now, initialize some private variables with default values
    m_vertical = false;
    //setVerticalMode(true);
    m_speed = 500;
    m_animationtype = QEasingCurve::InOutQuart;
    m_now = 0;
    m_next = 0;
    m_wrap = false;
    m_pnow = QPoint(0,0);
    m_active = false;

}

AnimatedStackedWidget::~AnimatedStackedWidget()
{

}

void
AnimatedStackedWidget::setVerticalMode(bool vertical) {
    m_vertical = vertical;
}

void
AnimatedStackedWidget::setSpeed(int speed) {
    m_speed = speed;
}

void
AnimatedStackedWidget::setAnimation(enum QEasingCurve::Type animationtype) {
    m_animationtype = animationtype;
}

void
AnimatedStackedWidget::setWrap(bool wrap) {
    m_wrap = wrap;
}

void
AnimatedStackedWidget::slideInNext() {
        int now = currentIndex();
        if (m_wrap || (now < count() - 1))
                // count is inherit from QStackedWidget
                slideInIdx(now + 1);
}


void
AnimatedStackedWidget::slideInPrev() {
        int now = currentIndex();
        if (m_wrap || (now > 0))
                slideInIdx(now - 1);
}

void
AnimatedStackedWidget::slideInIdx(int idx, enum t_effect direction) {
        //int idx, t_direction direction=AUTOMATIC
        if (idx > count() - 1) {
            direction = m_vertical ? TOP_BOTTOM : RIGHT_LEFT;

            idx = (idx) % count();
        }
        else if (idx < 0) {
            direction = m_vertical ? BOTTOM_TOP: LEFT_RIGHT;

            idx = (idx + count()) % count();
        }

        slideInWgt(widget(idx), direction);
        //widget() is a function inherited from QStackedWidget
}

void
AnimatedStackedWidget::slideInWgt(QWidget * newwidget, enum t_effect effect ) {

        if (m_active) {
            // at the moment, do not allow re-entrance before an animation is completed.
            //other possibility may be to finish the previous animation abrupt, or
            //to revert the previous animation with a counter animation, before going ahead
            //or to revert the previous animation abrupt
            //and all those only, if the newwidget is not the same as that of the previous running animation.
            return;
        }
        else m_active = true;

        enum t_effect directionhint;
        int now = currentIndex();
        int next = indexOf(newwidget);
        if (now == next) {
                m_active = false;
                return;
        }
        else if (now < next){
                directionhint = m_vertical ? TOP_BOTTOM : RIGHT_LEFT;
        }
        else {
                directionhint = m_vertical ? BOTTOM_TOP : LEFT_RIGHT;
        }
        if (effect == AUTOMATIC) {
                effect = directionhint;
        }
        //NOW....
        //calculate the shifts

        int offsetx = frameRect().width();
        int offsety = frameRect().height();

        //the following is important, to ensure that the new widget
        //has correct geometry information when sliding in first time
        widget(next)->setGeometry (0,  0, offsetx, offsety);

        //re-position the next widget outside/aside of the display area
        QPoint pnext = widget(next)->pos();
        QPoint pnow = widget(now)->pos();
        m_pnow = pnow;

        if (effect == BOTTOM_TOP)  {
                offsetx = 0;
                offsety = -offsety;
        }
        else if (effect == TOP_BOTTOM) {
                offsetx = 0;
                offsety = offsety;
        }
        else if (effect == RIGHT_LEFT) {
                offsetx = -offsetx;
                offsety = 0;
        }
        else if (effect == LEFT_RIGHT) {
                offsetx = offsetx;
                offsety = 0;
        }

        widget(next)->move(pnext.x() - offsetx, pnext.y() - offsety);
        //make it visible/show
        widget(next)->show();
        widget(next)->raise();

        //animate both, the now and next widget to the side, using animation framework
        QPropertyAnimation *animnow = new QPropertyAnimation(widget(now), "pos");
        animnow->setDuration(m_speed);
        animnow->setEasingCurve(m_animationtype);
        animnow->setStartValue(QPoint(pnow.x(), pnow.y()));
        animnow->setEndValue(QPoint(offsetx+pnow.x(), offsety+pnow.y()));

        QPropertyAnimation *animnext = new QPropertyAnimation(widget(next), "pos");
        animnext->setDuration(m_speed);
        animnext->setEasingCurve(m_animationtype);
        animnext->setStartValue(QPoint(-offsetx + pnext.x(), offsety + pnext.y()));
        animnext->setEndValue(QPoint(pnext.x(), pnext.y()));

        QParallelAnimationGroup *animgroup = new QParallelAnimationGroup;

        animgroup->addAnimation(animnow);
        animgroup->addAnimation(animnext);

        QObject::connect(animgroup, SIGNAL(finished()), this, SLOT(animationDoneSlot()));
        m_next = next;
        m_now = now;
        m_active = true;
        animgroup->start();

        //note; the rest is done via a connect from the animation ready;
        //animation->finished() provides a signal when animation is done;
        //so we connect this to some post processing slot,
        //that we implement here below in animationDoneSlot.
}


void
AnimatedStackedWidget::animationDoneSlot(void) {
    //when ready, call the QStackedWidget slot setCurrentIndex(int)
    setCurrentIndex(m_next);  //this function is inherit from QStackedWidget
    //then hide the outshifted widget now, and  (may be done already implicitely by QStackedWidget)
    widget(m_now)->hide();
    //then set the position of the outshifted widget now back to its original
    widget(m_now)->move(m_pnow);
    //so that the application could also still call the QStackedWidget original functions/slots for changings
    //widget(m_now)->update();
    //setCurrentIndex(m_next);  //this function is inherit from QStackedWidget
    m_active = false;
    emit animationFinished();
}
