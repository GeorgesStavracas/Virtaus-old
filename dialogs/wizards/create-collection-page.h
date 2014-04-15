#ifndef CREATECOLLECTIONPAGE_H
#define CREATECOLLECTIONPAGE_H

#include <QWizardPage>
#include "core/collection.h"
#include "core/data-writer.h"

namespace Ui {
class CreateCollectionPage;
}

class CreateCollectionPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit CreateCollectionPage(QWidget *parent = 0);
    ~CreateCollectionPage();

    void initializePage();

protected slots:
    void file_created(QString path);

private:
    Ui::CreateCollectionPage *ui;
};

#endif // CREATECOLLECTIONPAGE_H
