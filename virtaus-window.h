#ifndef VIRTAUSWINDOW_H
#define VIRTAUSWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QWizard>
#include "dialogs/about-dialog.h"
#include "collection-view.h"
#include "core/data-reader.h"
#include "dialogs/preferences-dialog.h"
#include "collection-view.h"
#include "virtaus-application.h"
#include "new-collection-wizard.h"

namespace Ui {
    class VirtausWindow;
}

class VirtausApplication;

class VirtausWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit VirtausWindow(VirtausApplication *app);
    ~VirtausWindow();

private slots:
    void show_about();
    void show_about_qt();
    void new_collection_wizard();
    void show_preferences();
    void show_home();
    void show_collection(Virtaus::Core::Collection* collection);

private:
    Ui::VirtausWindow *ui;
    VirtausApplication *app;
};

#endif // VIRTAUSWINDOW_H
