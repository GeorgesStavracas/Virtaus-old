#ifndef COLLECTIONVIEW_H
#define COLLECTIONVIEW_H

#include <QWidget>
#include <QStandardItem>
#include "core/collection.h"

namespace Ui {
class CollectionView;
}

class CollectionView : public QWidget
{
    Q_OBJECT

public:
    explicit CollectionView(QWidget *parent = 0);
    ~CollectionView();

    void setCollectionList (const QList<Virtaus::Collection>* list);

private:
    Ui::CollectionView *ui;
};

#endif // COLLECTIONVIEW_H
