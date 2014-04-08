#ifndef COLLECTIONINFOVIEW_H
#define COLLECTIONINFOVIEW_H

#include <QWidget>

namespace Ui {
class CollectionInfoView;
}

class CollectionInfoView : public QWidget
{
    Q_OBJECT

public:
    explicit CollectionInfoView(QWidget *parent = 0);
    ~CollectionInfoView();

private:
    Ui::CollectionInfoView *ui;
};

#endif // COLLECTIONINFOVIEW_H
