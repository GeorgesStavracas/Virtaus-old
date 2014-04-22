#include "collection-info-view.h"
#include "ui_collection-info-view.h"

CollectionInfoView::CollectionInfoView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CollectionInfoView)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(save()));
    timer->setInterval(10000);

    last = Virtaus::View::COLLECTION_VIEW;

    /* Setup tab order */
    this->setTabOrder(ui->featuresEdit, ui->requirementEdit);
    this->setTabOrder(ui->requirementEdit, ui->materialsEdit);
    this->setTabOrder(ui->materialsEdit, ui->finishingEdit);
    this->setTabOrder(ui->finishingEdit, ui->manufacturingEdit);
    this->setTabOrder(ui->manufacturingEdit, ui->suppliersEdit);
    this->setTabOrder(ui->suppliersEdit, ui->stylisticEdit);
    this->setTabOrder(ui->stylisticEdit, ui->functionalEdit);
    this->setTabOrder(ui->functionalEdit, ui->useEdit);
    this->setTabOrder(ui->useEdit, ui->feasibilityEdit);

    this->setTabOrder(ui->feasibilityEdit, ui->genreEdit);
    this->setTabOrder(ui->genreEdit, ui->physicalEdit);
    this->setTabOrder(ui->physicalEdit, ui->lifestyleEdit);
    this->setTabOrder(ui->lifestyleEdit, ui->productRequisitesEdit);
    this->setTabOrder(ui->productRequisitesEdit, ui->purchaseEdit);
    this->setTabOrder(ui->purchaseEdit, ui->desiresEdit);
    this->setTabOrder(ui->desiresEdit, ui->ageEdit);
    this->setTabOrder(ui->ageEdit, ui->valuesEdit);
    this->setTabOrder(ui->valuesEdit, ui->activitiesEdit);
    this->setTabOrder(ui->activitiesEdit, ui->attendingEdit);

    this->setTabOrder(ui->attendingEdit, ui->structureEdit);
    this->setTabOrder(ui->structureEdit, ui->productsEdit);
    this->setTabOrder(ui->productsEdit, ui->qualitiesEdit);

    ui->featuresEdit->setFocus();

    VirtausApplication* app = VirtausApplication::getInstance();

    QObject::connect(app, SIGNAL(view(Virtaus::View::Views)), this, SLOT(view_focus(Virtaus::View::Views)));

    QObject::connect(app, SIGNAL(collectionChanged(Virtaus::Core::Collection*)),
                        this, SLOT(collection_selected(Virtaus::Core::Collection*)));
}

CollectionInfoView::~CollectionInfoView()
{
    delete ui;
}

void
CollectionInfoView::back()
{
    VirtausApplication* app = VirtausApplication::getInstance();

    app->setView(Virtaus::View::COLLECTION_OPTIONS_VIEW);
}

void
CollectionInfoView::view_focus(Virtaus::View::Views view)
{
    if (view == Virtaus::View::COLLECTION_INFO_VIEW)
    {
        ui->featuresEdit->setFocus();
        timer->start();
    }

    if (view == Virtaus::View::COLLECTION_OPTIONS_VIEW &&
        last == Virtaus::View::COLLECTION_INFO_VIEW)
    {
        save();
        timer->stop();
    }

    last = view;
}

void
CollectionInfoView::collection_selected(Virtaus::Core::Collection* c)
{
    if (!c)
        return;


    ui->featuresEdit->setPlainText(c->getInfo("product-features"));
    ui->productRequisitesEdit->setPlainText(c->getInfo("product-requirement"));
    ui->materialsEdit->setText(c->getInfo("product-materials"));
    ui->finishingEdit->setText(c->getInfo("product-finishing"));
    ui->manufacturingEdit->setText(c->getInfo("product-manufacturing-proccess"));
    ui->suppliersEdit->setPlainText(c->getInfo("product-suppliers"));
    ui->functionalEdit->setPlainText(c->getInfo("product-functional-config"));
    ui->feasibilityEdit->setPlainText(c->getInfo("product-feasibility-analysis"));

    ui->genreEdit->setText(c->getInfo("audience-genre"));
    ui->physicalEdit->setPlainText(c->getInfo("audience-physical-features"));
    ui->lifestyleEdit->setPlainText(c->getInfo("audience-lifestyle"));
    ui->requirementEdit->setPlainText(c->getInfo("audience-requisites"));
    ui->purchaseEdit->setText(c->getInfo("audience-purchasing-power"));
    ui->desiresEdit->setPlainText(c->getInfo("audience-needs"));
    ui->ageEdit->setText(c->getInfo("audience-age"));
    ui->valuesEdit->setText(c->getInfo("audience-values"));
    ui->activitiesEdit->setPlainText(c->getInfo("audience-activities"));
    ui->attendingEdit->setPlainText(c->getInfo("audience-attending-places"));

    ui->structureEdit->setPlainText(c->getInfo("competitors-structure"));
    ui->productsEdit->setPlainText(c->getInfo("competitors-products"));
    ui->qualitiesEdit->setPlainText(c->getInfo("competitors-qualities"));
}

void
CollectionInfoView::save()
{
    /*
    VirtausApplication* app = VirtausApplication::getInstance();

    if (!app->collection())
        return;

    Virtaus::Core::DataWriter* writer;
    writer = new Virtaus::Core::DataWriter;

    writer->saveCollectionInfo(app->collection())
    */
    qDebug() << "Timer timeout";
}
