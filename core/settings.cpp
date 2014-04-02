#include "settings.h"

using namespace Virtaus::Core;

Settings* Virtaus::Core::Settings::instance = NULL;

Settings::Settings() : QObject()
{
    QDir* dir = new QDir;
    this->config_file = new QString(dir->currentPath()+"/config.ini");
    this->settings = new QSettings(*this->config_file, QSettings::NativeFormat);
}

void
Settings::setFile(QString &file)
{
    this->config_file->clear();
    this->config_file->append(file);

    delete this->settings;
    this->settings = new QSettings(*this->config_file, QSettings::NativeFormat);
}

Settings*
Settings::getInstance()
{
    if (!instance)
        instance = new Settings;

    return instance;
}
