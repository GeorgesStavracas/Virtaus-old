#ifndef VIRTAUSAPPLICATION_H
#define VIRTAUSAPPLICATION_H

#include <QtGui>
#include "core/collection.h"
#include "core/data-reader.h"
#include "core/data-writer.h"
#include "core/settings.h"
#include "virtaus-window.h"
#include "core/types.h"

namespace Ui {
    class VirtausApplication;
}

/*
 * Forward declarations
 */
class VirtausWindow;

/*
 * Class definition
 */
class VirtausApplication : public QApplication
{

    Q_OBJECT

    Q_PROPERTY(Virtaus::Core::Collection* collection READ collection WRITE setCollection NOTIFY collectionChanged)
    Q_PROPERTY(Virtaus::Core::Category* category READ category WRITE setCategory NOTIFY categoryChanged)
    Q_PROPERTY(Virtaus::Core::Item* item READ item WRITE setItem NOTIFY itemChanged)
    Q_PROPERTY(Virtaus::Core::Set* set READ set WRITE setSet NOTIFY setChanged)

public:
    static VirtausApplication* getInstance(int argc = 0, char ** argv = 0);

    /* GUI */
    void showGUI();

    /* Data manager */
    void loadData();

    QList<Virtaus::Core::Collection*>* getData();

    Virtaus::Core::Collection* collection() const {return c_collection;}
    Virtaus::Core::Category* category() const {return c_category;}
    Virtaus::Core::Item* item() const {return c_item;}
    Virtaus::Core::Set* set() const {return c_set;}

    Virtaus::View::Views view() const {return current_view;}

    void setCollection(Virtaus::Core::Collection* collection);
    void setCategory(Virtaus::Core::Category* category);
    void setItem(Virtaus::Core::Item* item);
    void setSet(Virtaus::Core::Set* set);

    void setView(Virtaus::View::Views view);
    void setState(Virtaus::State::State state);


signals:
    void collectionChanged(Virtaus::Core::Collection* c);
    void categoryChanged(Virtaus::Core::Category* c);
    void itemChanged(Virtaus::Core::Item* i);
    void setChanged(Virtaus::Core::Set* s);
    void view(Virtaus::View::Views view);

protected slots:
    void fsUpdate(const QString& path);
    void safeQuit();

protected:
    explicit VirtausApplication (int & argc, char ** argv);

    static VirtausApplication* instance;
    VirtausWindow *window;
    Virtaus::Core::DataReader *reader;
    Virtaus::Core::Settings* settings;
    QFileSystemWatcher* monitor;
    Virtaus::View::Views current_view;

    Virtaus::Core::Collection* c_collection;
    Virtaus::Core::Category* c_category;
    Virtaus::Core::Item* c_item;
    Virtaus::Core::Set* c_set;

    QList<Virtaus::Core::Collection*> *loaded_data;
};

#endif // VIRTAUSAPPLICATION_H
