#include "preferences-dialog.h"
#include "ui_preferences-dialog.h"

PreferencesDialog::PreferencesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferencesDialog)
{
    ui->setupUi(this);


    Virtaus::Core::Settings* settings;
    settings = Virtaus::Core::Settings::getInstance();

    ui->skinCombo->addItem(tr("Default"));

    ui->languageCombo->addItem(tr("System language"));

    ui->extensionCombo->addItem(tr("Default (.jpg)"));
    ui->extensionCombo->addItem(tr("Portable Network Graphic (.png)"));
    ui->extensionCombo->addItem(tr("Uncompressed data (.raw)"));
    ui->extensionCombo->addItem(tr("TIFF image (.tiff)"));

    ui->dirEdit->setText(settings->get("directory").toString());
    ui->nameEdit->setText(settings->get("user").toString());
    ui->emailEdit->setText(settings->get("email").toString());
    ui->openglBox->setChecked(settings->get("use-opengl").toBool());
}

PreferencesDialog::~PreferencesDialog()
{
    delete ui;
}

void
PreferencesDialog::save_settings(QAbstractButton* unused)
{
    Virtaus::Core::Settings* settings;
    settings = Virtaus::Core::Settings::getInstance();

    settings->set("use-opengl", ui->openglBox->isChecked());
    settings->set("directory", ui->dirEdit->text());
    settings->set("user", ui->nameEdit->text());
    settings->set("email", ui->emailEdit->text());

    settings->saveValues();
}
