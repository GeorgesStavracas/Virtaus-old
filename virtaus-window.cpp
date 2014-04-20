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

    QObject::connect(this->app, SIGNAL(view(Virtaus::View::Views)), this, SLOT(show_view(Virtaus::View::Views)));

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
VirtausWindow::show_view(Virtaus::View::Views view)
{
    switch (view)
    {
    case Virtaus::View::COLLECTION_VIEW:
        ui->setsView->setVisible(false);
        ui->mainStack->slideInIdx(0);
        break;

    case Virtaus::View::COLLECTION_OPTIONS_VIEW:
        ui->mainStack->slideInIdx(1);
        break;

    case Virtaus::View::SET_VIEW:
        ui->setsView->setVisible(true);
        ui->mainStack->slideInIdx(2);
        break;

    default:
        break;
    }
}

void
VirtausWindow::show_home()
{
    ui->mainStack->slideInIdx(0);
}
