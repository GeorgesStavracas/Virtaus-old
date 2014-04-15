#include "virtaus-window.h"
#include "ui_virtaus-window.h"

VirtausWindow::VirtausWindow(VirtausApplication *app) :
    QMainWindow(),
    ui(new Ui::VirtausWindow)
{
    ui->setupUi(this);

    ui->mainStack->setVerticalMode(true);
    ui->mainStack->setSpeed(750);

    this->app = app;
    this->app->loadData();

    ui->collectionView->setCollectionList(this->app->getData());
}

VirtausWindow::~VirtausWindow()
{
    delete ui;
}

void
VirtausWindow::show_about()
{
    AboutDialog *about = new AboutDialog(this);
    about->deleteLater();
    about->exec();
}

void
VirtausWindow::show_about_qt()
{
    this->app->aboutQt();
}

void
VirtausWindow::show_preferences()
{
    PreferencesDialog *dialog = new PreferencesDialog(this);
    dialog->deleteLater();
    dialog->exec();
}

void
VirtausWindow::new_collection_wizard()
{
    NewCollectionWizard *wizard = new NewCollectionWizard;

#ifdef __APPLE__
    wizard->setWizardStyle(QWizard::WizardStyle::MacStyle);
#endif

    wizard->deleteLater();
    wizard->exec();
}

void
VirtausWindow::show_collection(Virtaus::Core::Collection* collection)
{
    ui->collectionDataPage->reset();
    ui->mainStack->slideInIdx(1);
}

void
VirtausWindow::show_home()
{
    ui->mainStack->slideInIdx(0);
}
