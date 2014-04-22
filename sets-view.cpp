#include "sets-view.h"
#include "ui_sets-view.h"

SetsView::SetsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetsView)
{
    ui->setupUi(this);

    VirtausApplication* app = VirtausApplication::getInstance();

    Virtaus::Core::Settings* settings;
    settings = Virtaus::Core::Settings::getInstance();

    ui->cover->setAntialiasing(settings->get("antialiasing").toBool());
    ui->cover->setSmoothpixel(settings->get("smooth-pixel-interpolation").toBool());
    ui->cover->setDisableEffectOnAnimation(settings->get("disable-animation-effects").toBool());

    QObject::connect(app, SIGNAL(collectionChanged(Virtaus::Core::Collection*)),
                     this, SLOT(prepare_model(Virtaus::Core::Collection*)));
}

SetsView::~SetsView()
{
    delete ui;
}

void
SetsView::show_collections()
{
    VirtausApplication* app = VirtausApplication::getInstance();

    app->setView(Virtaus::View::COLLECTION_OPTIONS_VIEW);
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
