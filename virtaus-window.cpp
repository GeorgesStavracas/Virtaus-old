#include "virtaus-window.h"
#include "ui_virtaus-window.h"
#include <iostream>

VirtausWindow::VirtausWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VirtausWindow)
{
    ui->setupUi(this);

    collection_view = new CollectionView();

    ui->horizontalLayout->addWidget(this->collection_view);


    this->dialog = new PreferencesDialog(this);
    this->about = new AboutDialog(this);

    Virtaus::DataReader *reader = new Virtaus::DataReader;
    QLinkedList<Virtaus::Collection> *list = reader->loadData();

}

VirtausWindow::~VirtausWindow()
{
    delete ui;
}

void
VirtausWindow::show_about() {
    this->about->show();
}

void
VirtausWindow::new_collection_wizard() {
    NewCollectionWizard *wizard = new NewCollectionWizard;

#ifdef __APPLE__
    wizard->setWizardStyle(QWizard::WizardStyle::MacStyle);
#endif

    wizard->show();
}

void
VirtausWindow::show_preferences() {
    this->dialog->show();
}
