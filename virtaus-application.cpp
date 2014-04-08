#include "virtaus-application.h"

VirtausApplication::VirtausApplication (int & argc, char ** argv) :
    QApplication(argc, argv)
{
    this->window = new VirtausWindow(this);
    this->reader = new Virtaus::Core::DataReader;
    this->loaded_data = new QList<Virtaus::Core::Collection*>;
    this->settings = Virtaus::Core::Settings::getInstance();

    this->settings->setFile(this->applicationDirPath().append("/config.ini"));
}



void
VirtausApplication::showGUI()
{
    this->window->showMaximized();
}

void
VirtausApplication::loadData()
{
    QDir *dir = new QDir(QDir::homePath()+"/"+tr("My Collections"));

    if (!dir->exists())
        dir->mkdir(dir->absolutePath());

    /* Load the main list */
    this->loaded_data = this->reader->loadData(dir->absolutePath());


    delete dir;

}

QList<Virtaus::Core::Collection*>*
VirtausApplication::getData()
{
    return this->loaded_data;
}
