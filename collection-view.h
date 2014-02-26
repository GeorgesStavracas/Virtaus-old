#ifndef COLLECTIONVIEW_H
#define COLLECTIONVIEW_H

#include <QWidget>

namespace Ui {
class CollectionView;
}

class CollectionView : public QWidget
{
    Q_OBJECT

public:
    explicit CollectionView(QWidget *parent = 0);
    ~CollectionView();

private:
    Ui::CollectionView *ui;
};

#endif // COLLECTIONVIEW_H
