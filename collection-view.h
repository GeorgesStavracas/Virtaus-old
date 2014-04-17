#ifndef COLLECTIONVIEW_H
#define COLLECTIONVIEW_H

#include <QWidget>
#include <QStandardItem>
#include "core/collection.h"
#include "virtaus-application.h"
#include "core/types.h"

namespace Ui {
class CollectionView;
}

class CollectionView : public QWidget
{
    Q_OBJECT

public:
    explicit CollectionView(QWidget *parent = 0);
    ~CollectionView();

    void setCollectionList (QList<Virtaus::Core::Collection*>* list);

signals:
    void collectionSelected(Virtaus::Core::Collection* collection);

protected slots:
    void item_selected(QModelIndex index);

private:
    QList<Virtaus::Core::Collection*>* collections;
    Ui::CollectionView *ui;
};

#endif // COLLECTIONVIEW_H
