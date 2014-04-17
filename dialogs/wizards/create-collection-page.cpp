#include "create-collection-page.h"
#include "ui_create-collection-page.h"

int i = 0;

CreateCollectionPage::CreateCollectionPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::CreateCollectionPage)
{
    ui->setupUi(this);
    this->success = false;
}

CreateCollectionPage::~CreateCollectionPage()
{
    delete ui;
}

void
CreateCollectionPage::initializePage()
{
    Virtaus::Core::Collection* collection = new Virtaus::Core::Collection;

    QString collection_path = QDir::homePath()+"/"+tr("My Collections");
    collection_path += "/"+field("name").toString();

    collection->setInfo("name", field("name").toString());
    collection->setInfo("author", field("author").toString());
    collection->setInfo("email", field("email").toString());
    collection->setInfo("path", collection_path);

    Virtaus::Core::DataWriter* writer = new Virtaus::Core::DataWriter;
    QObject::connect(writer, SIGNAL(fileCreated(QString)), this, SLOT(file_created(QString)));
    success = writer->createCollection(collection);

    if (success)
        setFinalPage(true);
}

void
CreateCollectionPage::file_created(QString path)
{
    i++;

    ui->infoEdit->appendPlainText("Creating " + path + "...\n");

    ui->progressBar->setValue(i/3*100);
}
