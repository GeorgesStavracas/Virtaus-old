#include <QFileSystemModel>
#include "collection-view.h"
#include "ui_collection-view.h"

CollectionView::CollectionView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CollectionView)
{
    ui->setupUi(this);

    /* Test with filesystem */
    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());


    ui->listView->setModel(model);
}

CollectionView::~CollectionView()
{
    delete ui;
}
