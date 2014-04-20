#include <QFileSystemModel>
#include "collection-view.h"
#include "ui_collection-view.h"
#include <iostream>

CollectionView::CollectionView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CollectionView)
{
    ui->setupUi(this);

    this->collections = NULL;
}

CollectionView::~CollectionView()
{
    delete ui;
}

/*
 * Setup the collection model.
 */
void
CollectionView::setCollectionList (QList<Virtaus::Core::Collection*>* list) {
    if (!list) return;

    this->collections = list;

    QStandardItemModel *model = new QStandardItemModel;

    foreach (Virtaus::Core::Collection* collection, *list) {

        QIcon *icon = new QIcon (*collection->thumbnail);

        QStandardItem *item = new QStandardItem(*icon, collection->getInfo("name"));

        model->appendRow(item);
    }

    ui->listView->setModel(model);
}

void
CollectionView::item_selected(QModelIndex index) {
    if (!index.isValid()) return;

    /*
     * Since we're using QListView, it's sure that
     * the index.column() == 0 always. So we should
     * simply use index.row().
     */
    Virtaus::Core::Collection* collection = this->collections->at(index.row());

    VirtausApplication* app = VirtausApplication::getInstance();

    app->setCollection(collection);

    app->setView(Virtaus::View::COLLECTION_OPTIONS_VIEW);

    //emit collectionSelected(collection);

    qDebug() << "Collection" << collection->getInfo("name") << "selected";


}
