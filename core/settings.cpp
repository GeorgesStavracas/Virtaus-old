#include "settings.h"

using namespace Virtaus;

Settings* Virtaus::Settings::instance = NULL;

Settings::Settings() : QObject()
{
    QDir* dir = new QDir;
    this->config_file = new QString(dir->currentPath()+"/config.ini");
    qDebug() << (*this->config_file);
    this->settings = new QSettings(*this->config_file);
}

void
Settings::setFile(QString &file)
{
    this->config_file->clear();
    this->config_file->append(file);

    delete this->settings;
    this->settings = new QSettings(*this->config_file);

    qDebug() << (*this->config_file);
}

Settings*
Settings::getInstance()
{
    if (!instance) {
        instance = new Settings;
        qDebug() << "Instance created";
    }

    return instance;
}
