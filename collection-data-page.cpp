#include "collection-data-page.h"
#include "ui_collection-data-page.h"

CollectionDataPage::CollectionDataPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CollectionDataPage)
{
    ui->setupUi(this);

    ui->stack->setCurrentIndex(1);
}

CollectionDataPage::~CollectionDataPage()
{
    delete ui;
}


void
CollectionDataPage::go_info()
{
    ui->stack->slideInIdx(0);
}

void
CollectionDataPage::go_manager()
{
    ui->stack->slideInIdx(2);
}

void
CollectionDataPage::go_sets()
{
    ui->stack->slideInIdx(1);
}

void
CollectionDataPage::reset()
{
    ui->stack->slideInIdx(1);
}
