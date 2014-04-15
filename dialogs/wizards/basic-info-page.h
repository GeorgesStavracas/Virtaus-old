#ifndef BASICINFOPAGE_H
#define BASICINFOPAGE_H

#include <QWizardPage>
#include "core/data-reader.h"

namespace Ui {
class BasicInfoPage;
}

class BasicInfoPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit BasicInfoPage(QWidget *parent = 0);
    bool isComplete() const;
    int nextId() const;
    ~BasicInfoPage();

private:
    Ui::BasicInfoPage *ui;
    Virtaus::Core::DataReader *reader;
};

#endif // BASICINFOPAGE_H
