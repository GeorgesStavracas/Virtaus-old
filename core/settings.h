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

    template<typename T> T get(QString field)
    {
        std::string value = this->settings->value(field, "").toString().toStdString();
        std::stringstream ss(value);
        T t;
        ss >> t;
        return t;
    }

    void set(QString& field, QString& value)
    {
        this->settings->setValue(field, value);
    }

private:
    static Settings* instance;
    QString* config_file;
    QSettings* settings;

    Settings();

signals:

public slots:

};

#endif // SETTINGS_H
