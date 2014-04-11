#include "collection-data-page.h"
#include "ui_collection-data-page.h"

CollectionDataPage::CollectionDataPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CollectionDataPage)
{
    ui->setupUi(this);
}

CollectionDataPage::~CollectionDataPage()
{
    delete ui;
}
