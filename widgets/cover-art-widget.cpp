#include "cover-art-widget.h"
#include "ui_cover-art-widget.h"

CoverArtWidget::CoverArtWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CoverArtWidget)
{
    ui->setupUi(this);

    this->scene = new QGraphicsScene(this);
    //this->model = NULL;
}

CoverArtWidget::~CoverArtWidget()
{
    delete ui;

    delete scene;
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
