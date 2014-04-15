#ifndef COLLECTIONDATAPAGE_H
#define COLLECTIONDATAPAGE_H

#include <QWidget>
#include "virtaus-application.h"

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
    void set_view(Virtaus::View::Views view);

private:
    Ui::CollectionDataPage *ui;
};

#endif // COLLECTIONDATAPAGE_H
