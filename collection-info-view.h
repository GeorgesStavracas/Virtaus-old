#ifndef COLLECTIONINFOVIEW_H
#define COLLECTIONINFOVIEW_H

#include <QWidget>
#include "virtaus-application.h"

namespace Ui {
class CollectionInfoView;
}

class CollectionInfoView : public QWidget
{
    Q_OBJECT

public:
    explicit CollectionInfoView(QWidget *parent = 0);
    ~CollectionInfoView();

    void setApplication(VirtausApplication* app);

protected slots:
    void back();
    void view_focus(Virtaus::View::Views view);
    void collection_selected(Virtaus::Core::Collection* c);

signals:
    void goBack();

private:
    Ui::CollectionInfoView *ui;
    VirtausApplication* app;
};

#endif // COLLECTIONINFOVIEW_H
