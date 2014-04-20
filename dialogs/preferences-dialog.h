#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>
#include "virtaus-application.h"

namespace Ui {
class PreferencesDialog;
}

class PreferencesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreferencesDialog(QWidget *parent = 0);
    ~PreferencesDialog();

private:
    Ui::PreferencesDialog *ui;

protected slots:
    void save_settings(QAbstractButton* unused);
};

#endif // PREFERENCESDIALOG_H
