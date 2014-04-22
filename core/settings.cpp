#include "settings.h"

using namespace Virtaus::Core;

Settings* Virtaus::Core::Settings::instance = NULL;

Settings::Settings() : QObject()
{
    QDir* dir = new QDir;
    config_file = new QString(dir->absolutePath()+"/config.ini");
    settings = new QSettings("The Virtaus project", "Virtaus", this);
    settings->setPath(QSettings::NativeFormat, QSettings::UserScope, *config_file);

    this->map = new QMap<QString, QVariant>;
    map->insert("user-lang", "\"System\"");
    map->insert("image-format", ".png");
    map->insert("directory", QDir::homePath()+"/"+tr("My Collections"));
    map->insert("user", "");
    map->insert("email", "");
    map->insert("use-opengl", false);
    map->insert("antialiasing", true);
    map->insert("smooth-pixel-interpolation", true);
    map->insert("disable-animation-effects", false);
}

Settings::~Settings()
{
    foreach(QString key, map->keys())
        settings->setValue(key, map->value(key));

    delete settings;
}

void
Settings::setFile(QString &file)
{
    this->config_file->clear();
    this->config_file->append(file);

    delete settings;
    settings = new QSettings("The Virtaus project", "Virtaus", this);
    settings->setPath(QSettings::NativeFormat, QSettings::UserScope, file);

    loadValues();
}

void
Settings::loadValues()
{
    foreach (QString str, settings->allKeys())
        map->insert(str, settings->value(str));
}

void
Settings::saveValues()
{
    foreach(QString key, map->keys())
        settings->setValue(key, map->value(key));
}

Settings*
Settings::getInstance()
{
    if (!instance)
        instance = new Settings;

    return instance;
}

