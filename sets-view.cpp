#include "sets-view.h"
#include "ui_sets-view.h"

SetsView::SetsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetsView)
{
    ui->setupUi(this);

    VirtausApplication* app = VirtausApplication::getInstance();

    QObject::connect(app, SIGNAL(collectionSelected(Virtaus::Core::Collection*)),
                     this, SLOT(prepare_model(Virtaus::Core::Collection*)));
}

SetsView::~SetsView()
{
    delete ui;
}


void
SetsView::show_info()
{
    VirtausApplication* app = VirtausApplication::getInstance();

    app->setView(Virtaus::View::COLLECTION_INFO_VIEW);
}

void
SetsView::show_collections()
{
    VirtausApplication* app = VirtausApplication::getInstance();

    app->setView(Virtaus::View::COLLECTION_VIEW);
    app->setCurrent(NULL);
}

void
SetsView::show_categories()
{
    VirtausApplication* app = VirtausApplication::getInstance();

    app->setView(Virtaus::View::CATEGORY_VIEW);
}

void
SetsView::prepare_model(Virtaus::Core::Collection* c)
{
    if(!c) return;

    QStandardItemModel *model = new QStandardItemModel;

    foreach (Virtaus::Core::Set* set, c->getSets()->values()) {

        QIcon *icon = new QIcon (":/virtaus/images/resources/no_thumbnail.svg");
        QStandardItem *item = new QStandardItem(*icon, *set->getName());

        model->appendRow(item);
    }

    ui->cover->setModel(model);
}
