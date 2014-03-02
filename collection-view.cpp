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

/*
 * Setup the collection model.
 */
void
CollectionView::setCollectionList (const QList<Virtaus::Collection>* list) {
    if (!list) return;

    QStandardItemModel *model = new QStandardItemModel;

    foreach (Virtaus::Collection collection, *list) {

        QIcon *icon = new QIcon (*collection.thumbnail);

        QStandardItem *item = new QStandardItem(*icon, collection.getInfo("name"));

        model->appendRow(item);
    }

    ui->listView->setModel(model);
}
