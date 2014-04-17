#include "category-view.h"
#include "ui_category-view.h"

CategoryView::CategoryView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CategoryView)
{
    ui->setupUi(this);
}

CategoryView::~CategoryView()
{
    delete ui;
}
