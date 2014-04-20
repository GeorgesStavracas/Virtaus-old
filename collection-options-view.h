#ifndef COLLECTIONOPTIONSVIEW_H
#define COLLECTIONOPTIONSVIEW_H

#include <QWidget>
#include "core/types.h"
#include "virtaus-application.h"

namespace Ui {
class CollectionOptionsView;
}

class CollectionOptionsView : public QWidget
{
    Q_OBJECT

public:
    explicit CollectionOptionsView(QWidget *parent = 0);
    ~CollectionOptionsView();

protected slots:
    void show_info();
    void show_sets();
    void show_categories();
    void show_collections();
    void select_collection(Virtaus::Core::Collection* c);

private:
    Ui::CollectionOptionsView *ui;
};

#endif // COLLECTIONOPTIONSVIEW_H
