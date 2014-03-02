#ifndef DATAREADER_H
#define DATAREADER_H

#include <QtCore>
#include <QLinkedList>
#include <QXmlStreamReader>
#include <QtWidgets>
#include "collection.h"

namespace Virtaus {
    class DataReader;
}

class Virtaus::DataReader
{

public:
        DataReader();

        void setDir (const QString& dir);
        bool isValidPath (const QString& path);

        QString* getDir ();
        QList<Virtaus::Collection>* loadData();


protected:
        QString* dir;

        Virtaus::Collection* loadCollection (const QString& path);
        Virtaus::Category* loadCategory (const QString& path);
        bool isValidCategory (const QString& path);

};

#endif // DATAREADER_H
