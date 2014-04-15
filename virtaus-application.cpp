#include "virtaus-application.h"

VirtausApplication* VirtausApplication::instance = NULL;

VirtausApplication*
VirtausApplication::getInstance(int argc, char ** argv)
{
    if (!instance)
        instance = new VirtausApplication(argc, argv);

    return instance;
}

VirtausApplication::VirtausApplication (int & argc, char ** argv) :
    QApplication(argc, argv)
{
    this->reader = new Virtaus::Core::DataReader;
    this->loaded_data = new QList<Virtaus::Core::Collection*>;
    this->current = NULL;
    this->settings = Virtaus::Core::Settings::getInstance();

    this->settings->setFile(this->applicationDirPath().append("/config.ini"));
}



void
VirtausApplication::showGUI()
{
    this->window = new VirtausWindow(this);
    this->window->showMaximized();
}

Virtaus::Core::Collection*
VirtausApplication::getCurrent()
{
    return this->current;
}

void
VirtausApplication::setView(Virtaus::View::Views view)
{
    if (current_view != view)
        this->view(view);

    this->current_view = view;
}

void
VirtausApplication::setCurrent(Virtaus::Core::Collection *collection)
{
    this->current = collection;

    emit this->collectionSelected(collection);
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
