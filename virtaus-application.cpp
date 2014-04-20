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
    this->c_collection = NULL;
    this->settings = Virtaus::Core::Settings::getInstance();

    this->settings->setFile(this->applicationDirPath().append("/config.ini"));

    this->monitor = new QFileSystemWatcher(this);
    this->monitor->addPath(QDir::homePath()+"/"+tr("My Collections"));

    QObject::connect(monitor, SIGNAL(directoryChanged(QString)), this, SLOT(fsUpdate(QString)));

    QObject::connect(this, SIGNAL(aboutToQuit()), this, SLOT(safeQuit()));
}

void
VirtausApplication::safeQuit()
{
    settings->saveValues();
}

void
VirtausApplication::showGUI()
{
    this->window = new VirtausWindow(this);
    this->window->showMaximized();
}

void
VirtausApplication::fsUpdate(const QString &path)
{
    QDir* dir = new QDir(path);

    foreach (const QString & sub, dir->entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        QString final_path = path + "/" + sub;

        /* Directory added */
        if (dir->entryList(QDir::Dirs | QDir::NoDotAndDotDot).size() > loaded_data->size())
        {
            Virtaus::Core::Collection *col, *new_collection;

            bool contains = false;

            for (int i = 0; i < loaded_data->size(); i++)
            {
                col = loaded_data->at(i);

                if (col->getInfo("path") != sub)
                    continue;

                contains = true;
                break;
            }


            if (!contains)
            {
                if (reader->validateCollection(final_path))
                {
                    new_collection = reader->loadCollection(final_path);
                    loaded_data->append(new_collection);
                    //emit update()
                }
            }
        }

        /* Directory removed */
        if (dir->entryList(QDir::Dirs | QDir::NoDotAndDotDot).size() < loaded_data->size())
        {
            /* TODO */
        }
    }
}

void
VirtausApplication::setView(Virtaus::View::Views view)
{
    if (current_view != view)
        this->view(view);

    this->current_view = view;
}

void
VirtausApplication::setCollection(Virtaus::Core::Collection *collection)
{
    this->c_collection = collection;

    emit collectionChanged(collection);
}


void
VirtausApplication::setCategory(Virtaus::Core::Category *category)
{
    this->c_category = category;

    emit categoryChanged(category);
}

void
VirtausApplication::setItem(Virtaus::Core::Item *item)
{
    this->c_item = item;

    emit itemChanged(item);
}

void
VirtausApplication::setSet(Virtaus::Core::Set *set)
{
    this->c_set = set;

    emit setChanged(set);
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
