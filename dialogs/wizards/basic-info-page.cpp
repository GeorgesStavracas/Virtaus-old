#include "basic-info-page.h"
#include "ui_basic-info-page.h"
#include <iostream>

BasicInfoPage::BasicInfoPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::BasicInfoPage)
{
    ui->setupUi(this);

    this->reader = new Virtaus::Core::DataReader;

    registerField("name*", ui->nameEdit);
    registerField("author*", ui->authorEdit);
    registerField("email*", ui->mailEdit);

}

bool
BasicInfoPage::isComplete() const {

    QRegExp *exp = new QRegExp("[\\\\/<>\\=\\{\\}]");
    bool v_author = false, v_name = false, v_mail = false;
    QDir *dir = new QDir(QDir::homePath()+"/"+tr("My Collections"));



    /* Checking title */
    if (ui->nameEdit->text().contains(*exp)) {
        ui->nameEdit->setStyleSheet("QLineEdit { color: red; }");
        ui->errorLabel->setVisible(false);
        v_name = false;

    }
    else {
        if (dir->entryList(QDir::Dirs).contains(ui->nameEdit->text())) {
            ui->nameEdit->setStyleSheet("QLineEdit { color: red; }");
            ui->errorLabel->setVisible(true);
            v_name = false;
        } else {
            ui->nameEdit->setStyleSheet("");
            ui->errorLabel->setVisible(false);
            v_name = true;
        }
    }



    /* Checking author */
    if (ui->authorEdit->text().contains(*exp)){
        ui->authorEdit->setStyleSheet("QLineEdit { color: red; }");
        v_author = false;
    }
    else {
        ui->authorEdit->setStyleSheet("");
        v_author = true;
    }

    delete exp;



    /* Checking email */
    exp = new QRegExp("^[_A-Za-z0-9-\\+]+(\\.[_A-Za-z0-9-]+)*@[A-Za-z0-9-]+(\\.[A-Za-z0-9]+)*(\\.[A-Za-z]{2,})$");

    if (!ui->mailEdit->text().contains(*exp)) {
        ui->mailEdit->setStyleSheet("QLineEdit { color: red; }");
        v_mail = false;

        if (ui->mailEdit->text()=="") {
            ui->mailEdit->setStyleSheet("");
            v_mail = true;
        }
    }
    else {
        ui->mailEdit->setStyleSheet("");
        v_mail = true;
    }

    if (!v_author || ui->authorEdit->text()=="")
        return false;
    if (!v_name || ui->nameEdit->text()=="")
        return false;
    if (!v_mail)
        return false;

    return true;
}

int
BasicInfoPage::nextId() const {
    return 2;
}

BasicInfoPage::~BasicInfoPage()
{
    delete ui;
}
