#include "collection-data-page.h"
#include "ui_collection-data-page.h"

CollectionDataPage::CollectionDataPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CollectionDataPage)
{
    ui->setupUi(this);

    ui->stack->setCurrentIndex(1);

    VirtausApplication* app = VirtausApplication::getInstance();
    QObject::connect(app, SIGNAL(view(Virtaus::View::Views)), this, SLOT(set_view(Virtaus::View::Views)));
}

CollectionDataPage::~CollectionDataPage()
{
    delete ui;
}


void
CollectionDataPage::set_view(Virtaus::View::Views view)
{
    switch(view) {
    case Virtaus::View::SET_VIEW:
        ui->stack->slideInIdx(1);
        break;

    case Virtaus::View::COLLECTION_INFO_VIEW:
        ui->stack->slideInIdx(0);
        break;

    case Virtaus::View::CATEGORY_VIEW:
        ui->stack->slideInIdx(1);
        break;

    default:
        break;
    }
}

void
CollectionDataPage::reset()
{
    ui->stack->slideInIdx(1);
}
