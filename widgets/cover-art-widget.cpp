#include "cover-art-widget.h"
#include "ui_cover-art-widget.h"

CoverArtWidget::CoverArtWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CoverArtWidget)
{
    ui->setupUi(this);

    this->setMouseTracking(true);

    this->scene = new CoverArtScene();
    this->scene->setBackgroundBrush(QBrush(QColor(53,53,55)));
    this->scene->setItemIndexMethod(QGraphicsScene::BspTreeIndex);
    this->scene->setCurrentItem(0);

    ui->graphicsView->setScene(scene);

    this->itemList = new QList<CoverArtItem*>;
    this->speed = 1000;
    this->stack_move = 50;
    this->center_padding = 50;

    QObject::connect(scene, SIGNAL(itemSelected(int)), this, SLOT(selection_changed(int)));
}

CoverArtWidget::~CoverArtWidget()
{
    delete ui;

    delete scene;
}

void
CoverArtWidget::setModel(QStandardItemModel *list)
{
    if (!list)
        qDebug() << "NULL model";

    this->model = list;

    foreach (QGraphicsItem* it, scene->items())
    {
        scene->removeItem(it);
        delete it;
    }

    itemList->clear();

    /* NULL model cleanup */
    if (!list)
        return;


    for(int i = 0; i < list->rowCount(); i++)
    {
        CoverArtItem *item = new CoverArtItem;
        item->setItem(list->item(i));
        item->setIndex(i);
        itemList->append(item);
    }

    /* Last default item */
    CoverArtItem *item = new CoverArtItem;
    QIcon *icon = new QIcon (":/virtaus/images/resources/add_new.svg");
    QStandardItem* stditem = new QStandardItem(*icon, "");
    item->setItem(stditem);
    item->setIsLast(true);
    item->setIndex(list->rowCount());

    itemList->append(item);

    scene->setCurrentItem(0);
    place_widgets();

    ui->horizontalScrollBar->setMaximum(itemList->size()-1);
}

void
CoverArtWidget::place_widgets()
{
    int current = scene->currentItem();


    ui->horizontalScrollBar->setValue(current);

    ui->graphicsView->setRenderHint(QPainter::SmoothPixmapTransform, false);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing, false);

    CoverArtItem* item;
    int item_size = scene->sceneRect().height() * 0.6;

    // Place CURRENT item
    item = itemList->at(current);
    item->setSize(item_size, item_size);
    item->setX(-item_size/2);
    item->setY(-item_size/2);
    item->setYRotation(0);
    item->setSelected(true);

    if(!scene->items().contains(item))
        scene->addItem(item);


    // Place items at RIGHT
    for (int i = current + 1; i < itemList->size(); i++)
    {
        item = itemList->at(i);

        item->setSize(item_size, item_size);
        item->setSelected(false);
        item->setOrigin(QPointF(item->size().width(), 0));

        QTransform trans;
        trans.translate(item_size, item_size/2);
        trans.rotate(60, Qt::YAxis);
        trans.translate(-item_size, -item_size/2);
        item->setTransform(trans);
        item->setYRotation(60);

        int x = (i - current - 1) * stack_move + 10;
        int y = -item_size/2;

        item->setX(x);
        item->setY(y);

        item->setZValue(current - i);

        if(!scene->items().contains(item))
            scene->addItem(item);
    }

    // Place items at LEFT
    for (int i = 0; i < current; i++)
    {
        item = itemList->at(i);

        item->setSize(item_size, item_size);
        item->setSelected(false);
        item->setOrigin(QPointF(0, 0));

        QTransform trans;
        trans.translate(0, item_size/2);
        trans.rotate(-60, Qt::YAxis);
        trans.translate(0, -item_size/2);
        item->setTransform(trans);
        item->setYRotation(-60);

        int transformedWidth = item->boundingRegion(trans).boundingRect().width();

        int x = (i - current + 1) * stack_move;
        x -= item_size/2 + transformedWidth + center_padding;
        int y = -item_size/2;

        item->setX(x);
        item->setY(y);

        item->setZValue(i - current);

        if(!scene->items().contains(item))
            scene->addItem(item);
    }

    ui->graphicsView->setRenderHint(QPainter::SmoothPixmapTransform);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
}

void
CoverArtWidget::resizeEvent(QResizeEvent* event)
{
    int height = event->size().height() - ui->horizontalScrollBar->height();
    int width = event->size().width();
    scene->setSceneRect(-width/2,  -height/2, width, height);
    scene->update(-width/2,-height/2,width,height);

    place_widgets();
}

void
CoverArtWidget::selection_changed(int index)
{
    int local_index = index;

    if (index < 0)
        local_index = 0;

    if (index == -3)
        local_index = 0;

    if (index == -2)
        local_index = itemList->size()-1;

    if (index >= itemList->size())
        local_index = itemList->size()-1;

    slideTo(local_index);
    scene->setCurrentItem(local_index);
    ui->horizontalScrollBar->setValue(local_index);
}

void
CoverArtWidget::slideTo(int index)
{
    if (scene->currentItem() < 0 || index == scene->currentItem())
        return;

    ui->graphicsView->setRenderHint(QPainter::SmoothPixmapTransform, false);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing, false);

    QParallelAnimationGroup* group = new QParallelAnimationGroup;

    int item_size = scene->sceneRect().height() * 0.6;
    int middle = item_size / 2;


    /* Animate CURRENT item */
    CoverArtItem* item;

    item = itemList->at(index);
    item->setSize(item_size, item_size);
    item->setZValue(1);
    item->setSelected(true);

    QPropertyAnimation *current_pos = new QPropertyAnimation(item, "pos");
    current_pos->setDuration(speed*1.5);
    current_pos->setEasingCurve(QEasingCurve::OutQuint);
    current_pos->setStartValue(item->pos());
    current_pos->setEndValue(QPoint(-middle, -middle));

    QPropertyAnimation *current_rot = new QPropertyAnimation(item, "yrotation");
    current_rot->setDuration(speed*1.5);
    current_rot->setEasingCurve(QEasingCurve::OutQuint);
    current_rot->setStartValue(item->yrotation());
    current_rot->setEndValue(0);

    QPropertyAnimation *current_origin = new QPropertyAnimation(item, "origin");
    current_origin->setDuration(speed*1.5);
    current_origin->setEasingCurve(QEasingCurve::OutQuint);
    current_origin->setStartValue(item->origin());
    current_origin->setEndValue(QPointF(0,0));

    group->addAnimation(current_pos);
    group->addAnimation(current_rot);
    group->addAnimation(current_origin);

    // Animate items at RIGHT
    for (int i = index + 1; i < itemList->size(); i++)
    {
        item = itemList->at(i);

        item->setSize(item_size, item_size);
        item->setSelected(false);

        int x = (i - index - 1) * stack_move + 10;

        QPropertyAnimation *right_pos = new QPropertyAnimation(item, "pos");
        right_pos->setDuration(speed);
        right_pos->setEasingCurve(QEasingCurve::OutQuint);
        right_pos->setStartValue(item->pos());
        right_pos->setEndValue(QPointF(x, -middle));

        QPropertyAnimation *right_rot = new QPropertyAnimation(item, "yrotation");
        right_rot->setDuration(speed);
        right_rot->setEasingCurve(QEasingCurve::OutQuint);
        right_rot->setStartValue(item->yrotation());
        right_rot->setEndValue(60);

        QPropertyAnimation *right_origin = new QPropertyAnimation(item, "origin");
        right_origin->setDuration(speed);
        right_origin->setEasingCurve(QEasingCurve::OutQuint);
        right_origin->setStartValue(item->origin());
        right_origin->setEndValue(QPointF(item->size().width(),0));

        item->setZValue(index - i);

        group->addAnimation(right_pos);
        group->addAnimation(right_rot);
        group->addAnimation(right_origin);
    }

    // Animate items at LEFT
    for (int i = 0; i < index; i++)
    {
        item = itemList->at(i);

        item->setSize(item_size, item_size);
        item->setSelected(false);

        QTransform trans;
        trans.translate(0, 0);
        trans.rotate(-60, Qt::YAxis);
        trans.translate(0, 0);

        int transformedWidth = item->boundingRegion(trans).boundingRect().width();

        int x = (i - index + 1) * stack_move;
        x -= middle + transformedWidth + center_padding;

        QPropertyAnimation *left_pos = new QPropertyAnimation(item, "pos");
        left_pos->setDuration(speed);
        left_pos->setEasingCurve(QEasingCurve::OutQuint);
        left_pos->setStartValue(item->pos());
        left_pos->setEndValue(QPointF(x, -middle));

        QPropertyAnimation *left_rot = new QPropertyAnimation(item, "yrotation");
        left_rot->setDuration(speed);
        left_rot->setEasingCurve(QEasingCurve::OutQuint);
        left_rot->setStartValue(item->yrotation());
        left_rot->setEndValue(-60);

        QPropertyAnimation *left_origin = new QPropertyAnimation(item, "origin");
        left_origin->setDuration(speed);
        left_origin->setEasingCurve(QEasingCurve::OutQuint);
        left_origin->setStartValue(item->origin());
        left_origin->setEndValue(QPointF(0,0));

        item->setZValue(i - index);

        group->addAnimation(left_pos);
        group->addAnimation(left_rot);
        group->addAnimation(left_origin);

    }

    group->start(QAbstractAnimation::DeleteWhenStopped);

    QObject::connect(group, SIGNAL(finished()), this, SLOT(animationFinished()));
}

void
CoverArtWidget::animationFinished()
{
    ui->graphicsView->setRenderHint(QPainter::SmoothPixmapTransform);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
}
