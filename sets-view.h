#ifndef SETSVIEW_H
#define SETSVIEW_H

#include <QWidget>

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
    void show_info();
    void show_products();

signals:
    void showInfo();
    void showProducts();

private:
    Ui::SetsView *ui;
};

#endif // SETSVIEW_H
