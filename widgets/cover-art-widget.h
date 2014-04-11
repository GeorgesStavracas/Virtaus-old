#ifndef COVERARTWIDGET_H
#define COVERARTWIDGET_H

#include <QWidget>

namespace Ui {
class CoverArtWidget;
}

class CoverArtWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CoverArtWidget(QWidget *parent = 0);
    ~CoverArtWidget();

private:
    Ui::CoverArtWidget *ui;
};

#endif // COVERARTWIDGET_H
