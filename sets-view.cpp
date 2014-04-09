#include "sets-view.h"
#include "ui_sets-view.h"

SetsView::SetsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetsView)
{
    ui->setupUi(this);
}

SetsView::~SetsView()
{
    delete ui;
}
