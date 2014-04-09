#ifndef VIRTAUSAPPLICATION_H
#define VIRTAUSAPPLICATION_H

#include <QtGui>
#include "core/collection.h"
#include "core/data-reader.h"
#include "core/data-writer.h"
#include "core/settings.h"
#include "virtaus-window.h"

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

public:
    explicit VirtausApplication (int & argc, char ** argv);

    /* GUI */
    void showGUI();

    /* Data manager */
    void loadData();

    QList<Virtaus::Core::Collection*>* getData();

    Virtaus::Core::Collection* getCurrent();

    void setCurrent(Virtaus::Core::Collection* collection);


signals:

public slots:

protected:
    VirtausWindow *window;
    Virtaus::Core::DataReader *reader;
    Virtaus::Core::Settings* settings;

    Virtaus::Core::Collection* current;

    QList<Virtaus::Core::Collection*> *loaded_data;
};

#endif // VIRTAUSAPPLICATION_H
