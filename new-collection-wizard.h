#ifndef NEWCOLLECTIONWIZARD_H
#define NEWCOLLECTIONWIZARD_H

#include <QWizard>
#include "basic-info-page.h"

namespace Ui {
class NewCollectionWizard;
}

class NewCollectionWizard : public QWizard
{
    Q_OBJECT

public:
    explicit NewCollectionWizard(QWidget *parent = 0);
    ~NewCollectionWizard();

private:
    Ui::NewCollectionWizard *ui;
};

#endif // NEWCOLLECTIONWIZARD_H
