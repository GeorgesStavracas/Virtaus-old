#ifndef COLLECTIONINFOVIEW_H
#define COLLECTIONINFOVIEW_H

#include <QWidget>
#include "virtaus-application.h"
#include "core/data-writer.h"

namespace Ui {
class CollectionInfoView;
}

class CollectionInfoView : public QWidget
{
    Q_OBJECT

public:
    explicit CollectionInfoView(QWidget *parent = 0);
    ~CollectionInfoView();

protected slots:
    void back();
    void view_focus(Virtaus::View::Views view);
    void collection_selected(Virtaus::Core::Collection* c);
    void save();

signals:
    void goBack();

private:
    QTimer* timer;
    Ui::CollectionInfoView *ui;
    Virtaus::View::Views last;
};

#endif // COLLECTIONINFOVIEW_H
