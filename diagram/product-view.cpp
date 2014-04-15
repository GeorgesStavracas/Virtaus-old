#include "product-view.h"
#include "ui_product-view.h"
#include <iostream>

ProductView::ProductView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductView)
{
    ui->setupUi(this);

    ui->stackedWidget->slideInIdx(1);
}

ProductView::~ProductView()
{
    delete ui;
}

void
ProductView::show_diagram_view(){
    ui->stackedWidget->slideInIdx(2);
}

void
ProductView::show_product_view(){
    ui->stackedWidget->slideInIdx(1);
}

void
ProductView::show_info_view(){
    ui->stackedWidget->slideInIdx(0);
}

void
ProductView::setCollection (Virtaus::Core::Collection* collection) {

    ui->stackedWidget->setCurrentIndex(1);

    //ui->diagramView->setCollection(collection);
}

void
DiagramView::item_selected() {

}
