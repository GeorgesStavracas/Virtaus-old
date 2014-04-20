#include "collection-options-view.h"
#include "ui_collection-options-view.h"

CollectionOptionsView::CollectionOptionsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CollectionOptionsView)
{
    ui->setupUi(this);


    VirtausApplication* app = VirtausApplication::getInstance();

    QObject::connect(app, SIGNAL(collectionChanged(Virtaus::Core::Collection*)),
                        this, SLOT(select_collection(Virtaus::Core::Collection*)));
}

CollectionOptionsView::~CollectionOptionsView()
{
    delete ui;
}

void
CollectionOptionsView::show_info()
{
    VirtausApplication* app = VirtausApplication::getInstance();

    app->setView(Virtaus::View::COLLECTION_INFO_VIEW);
}

void
CollectionOptionsView::show_sets()
{
    VirtausApplication* app = VirtausApplication::getInstance();

    app->setView(Virtaus::View::SET_VIEW);
}

void
CollectionOptionsView::show_categories()
{
    VirtausApplication* app = VirtausApplication::getInstance();

    app->setView(Virtaus::View::CATEGORY_VIEW);
}

void
CollectionOptionsView::show_collections()
{
    VirtausApplication* app = VirtausApplication::getInstance();

    app->setView(Virtaus::View::COLLECTION_VIEW);
    app->setCollection(NULL);
}

void
CollectionOptionsView::select_collection(Virtaus::Core::Collection* c)
{
    if (c)
        ui->collectionName->setText(c->getInfo("name"));
}
