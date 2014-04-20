#include "collection-info-view.h"
#include "ui_collection-info-view.h"

CollectionInfoView::CollectionInfoView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CollectionInfoView)
{
    ui->setupUi(this);

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

    this->setTabOrder(ui->feasibilityEdit, ui->genreCombo);
    this->setTabOrder(ui->genreCombo, ui->physicalEdit);
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

void
CollectionInfoView::setApplication(VirtausApplication *app)
{
    this->app = app;
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
        ui->featuresEdit->setFocus();
}

void
CollectionInfoView::collection_selected(Virtaus::Core::Collection* c)
{
    if (!c)
        return;

    ui->featuresEdit->setPlainText(c->getInfo("product-features"));
}
