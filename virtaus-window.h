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
#include "new-collection-wizard.h"

namespace Ui {
    class VirtausWindow;
}

class VirtausWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit VirtausWindow(QWidget *parent = 0);
    ~VirtausWindow();

private slots:
    void show_about();
    void new_collection_wizard();
    void show_preferences();

private:
    Ui::VirtausWindow *ui;
};

#endif // VIRTAUSWINDOW_H
