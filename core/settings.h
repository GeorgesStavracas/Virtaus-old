#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtCore>
#include <QSettings>

namespace Virtaus {
    class Settings;
}

class VirtausApplication;

class Virtaus::Settings : public QObject
{

    Q_OBJECT

public:
    static Virtaus::Settings* getInstance();

    void setFile(QString& file);

    template<typename T> T setting(QString& field);

private:
    static Settings* instance;
    QString* config_file;
    QSettings* settings;

    Settings();

signals:

public slots:

};

#endif // SETTINGS_H
