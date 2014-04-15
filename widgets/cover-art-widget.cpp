#include "cover-art-widget.h"
#include "ui_cover-art-widget.h"

CoverArtWidget::CoverArtWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CoverArtWidget)
{
    ui->setupUi(this);

    this->scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    this->itemList = new QList<QGraphicsItem*>;
    this->current = 2;

    /* Test code */
    ImageGraphicItem* item = new ImageGraphicItem;
    this->itemList->append(item);

    item = new ImageGraphicItem;
    this->itemList->append(item);

    item = new ImageGraphicItem;
    this->itemList->append(item);

    item = new ImageGraphicItem;
    this->itemList->append(item);

    item = new ImageGraphicItem;
    this->itemList->append(item);

    item = new ImageGraphicItem;
    this->itemList->append(item);

    //this->model = NULL;
    this->order_widgets();
}

CoverArtWidget::~CoverArtWidget()
{
    delete ui;

    delete scene;
}

void
CoverArtWidget::order_widgets()
{
    this->scene->setSceneRect(0,0,this->size().width(),this->size().height());
    qDebug() << this->size().width() << this->size().height();

    int right = this->current - this->itemList->size();

    QGraphicsItem* current_item = this->itemList->at(this->current);

    for (int i = 0; i < this->current - 1; i++) {
        QGraphicsItem* item = this->itemList->at(i);
        item->setX(i*10);
    }
}

/*
void
CoverArtWidget::setModel (QAbstractListModel model)
{
    this->model = &model;

    model.children();
}

QAbstractListModel
CoverArtWidget::getModel()
{
    return *model;
}
*/
