#include "virtaus-window.h"
#include "ui_virtaus-window.h"
#include <iostream>

VirtausWindow::VirtausWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VirtausWindow)
{
    ui->setupUi(this);

    Virtaus::DataReader *reader = new Virtaus::DataReader;
    QList<Virtaus::Collection> *list = reader->loadData();

    ui->collectionView->setCollectionList(list);
}

VirtausWindow::~VirtausWindow()
{
    delete ui;
}

void
VirtausWindow::show_about() {
    AboutDialog *about = new AboutDialog(this);
    about->deleteLater();
    about->exec();
}

void
VirtausWindow::show_preferences() {
    PreferencesDialog *dialog = new PreferencesDialog(this);

#ifdef Q_OS_WIN
    dialog->setStyleSheet("QDialog {\n	background-color: rgb(255, 255, 255);\n}");
#endif

    dialog->deleteLater();
    dialog->exec();
}

void
VirtausWindow::new_collection_wizard() {
    NewCollectionWizard *wizard = new NewCollectionWizard;

#ifdef __APPLE__
    wizard->setWizardStyle(QWizard::WizardStyle::MacStyle);
#endif

    wizard->deleteLater();
    wizard->exec();
}

