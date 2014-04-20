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

public:
    static VirtausApplication* getInstance(int argc = 0, char ** argv = 0);

    /* GUI */
    void showGUI();

    /* Data manager */
    void loadData();

    QList<Virtaus::Core::Collection*>* getData();

    Virtaus::Core::Collection* collection() const {return c_collection;}

    void setCollection(Virtaus::Core::Collection* collection);
    void setView(Virtaus::View::Views view);
    void setState(Virtaus::State::State state);


signals:
    void collectionChanged(Virtaus::Core::Collection* c);
    void view(Virtaus::View::Views view);

protected slots:
    void fsUpdate(const QString& path);

protected:
    explicit VirtausApplication (int & argc, char ** argv);

    static VirtausApplication* instance;
    VirtausWindow *window;
    Virtaus::Core::DataReader *reader;
    Virtaus::Core::Settings* settings;
    QFileSystemWatcher* monitor;
    Virtaus::View::Views current_view;

    Virtaus::Core::Collection* c_collection;

    QList<Virtaus::Core::Collection*> *loaded_data;
};

#endif // VIRTAUSAPPLICATION_H
