#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtCore>
#include <QSettings>
#include <string>
#include <sstream>
#include <iostream>

namespace Virtaus {
    namespace Core {
        class Settings;
    }
}

class Virtaus::Core::Settings : public QObject
{

    Q_OBJECT

public:
    static Virtaus::Core::Settings* getInstance();

    void setFile(QString& file);

    void loadValues();
    void saveValues();

    QVariant get(const QString& field, const QVariant& def = "")
    {
        if (def != "")
            return settings->value(field, def);
        else
            return settings->value(field, map->value(field));
    }

    void set(QString field, QVariant value)
    {
        map->insert(field, value);
        settings->setValue(field, value);
    }

private:
    static Settings* instance;

    Settings();
    ~Settings();

    QString* config_file;
    QSettings* settings;
    QMap<QString, QVariant>* map;

};

#endif // SETTINGS_H
