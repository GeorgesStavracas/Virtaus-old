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

    QList<Virtaus::Collection*>* getData();


signals:

public slots:

protected:
    VirtausWindow *window;
    Virtaus::DataReader *reader;
    Virtaus::Settings* settings;

    QList<Virtaus::Collection*> *loaded_data;
};

#endif // VIRTAUSAPPLICATION_H
