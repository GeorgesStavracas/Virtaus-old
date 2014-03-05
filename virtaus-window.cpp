#include "virtaus-window.h"
#include "ui_virtaus-window.h"

VirtausWindow::VirtausWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VirtausWindow)
{
    ui->setupUi(this);

    ui->mainStack->setVerticalMode(true);
    ui->mainStack->setSpeed(750);

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

void
VirtausWindow::show_collection(Virtaus::Collection collection) {

    ui->productView->setCollection(&collection);
    ui->mainStack->slideInNext();

}

void
VirtausWindow::show_home() {
    ui->mainStack->slideInPrev();
}
