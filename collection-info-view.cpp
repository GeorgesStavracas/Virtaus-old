#include "collection-info-view.h"
#include "ui_collection-info-view.h"

CollectionInfoView::CollectionInfoView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CollectionInfoView)
{
    ui->setupUi(this);
}

CollectionInfoView::~CollectionInfoView()
{
    delete ui;
}
