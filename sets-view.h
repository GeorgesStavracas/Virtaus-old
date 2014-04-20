#ifndef SETSVIEW_H
#define SETSVIEW_H

#include <QWidget>
#include "virtaus-application.h"

namespace Ui {
class SetsView;
}

class SetsView : public QWidget
{
    Q_OBJECT

public:
    explicit SetsView(QWidget *parent = 0);
    ~SetsView();

protected slots:
    void show_collections();
    void prepare_model(Virtaus::Core::Collection* c);

private:
    Ui::SetsView *ui;
};

#endif // SETSVIEW_H
