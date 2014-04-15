#ifndef COLLECTIONDATAPAGE_H
#define COLLECTIONDATAPAGE_H

#include <QWidget>

namespace Ui {
class CollectionDataPage;
}

class CollectionDataPage : public QWidget
{
    Q_OBJECT

public:
    explicit CollectionDataPage(QWidget *parent = 0);
    ~CollectionDataPage();

    void reset();

protected slots:
    void go_info();
    void go_manager();
    void go_sets();

private:
    Ui::CollectionDataPage *ui;
};

#endif // COLLECTIONDATAPAGE_H
