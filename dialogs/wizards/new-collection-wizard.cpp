#include "new-collection-wizard.h"
#include "ui_new-collection-wizard.h"
#include <iostream>

NewCollectionWizard::NewCollectionWizard(QWidget *parent) :
    QWizard(parent),
    ui(new Ui::NewCollectionWizard)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
}

NewCollectionWizard::~NewCollectionWizard()
{
    delete ui;
}
