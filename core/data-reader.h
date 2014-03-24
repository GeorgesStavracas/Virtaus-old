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

class Virtaus::DataReader :
        public QObject
{

    Q_OBJECT

public:
        DataReader();

        QList<Virtaus::Collection*>* loadData(const QString& path);

        /* Validating methods */
        bool validateAttribute(const QString& path);
        bool validateCategory(const QString& path);
        bool validateCollection(const QString& path);

        /* Auxiliary methods */
        bool hasItem (const QString& path, const QString& item);
        bool hasProduct (const QString& path, const QString& product);

protected:
        /* Loading methods */
        Virtaus::Attribute* loadAttribute (const QString& path, Virtaus::Category* parent);
        Virtaus::Category* loadCategory (const QString& path, Virtaus::Collection* parent);
        Virtaus::Collection* loadCollection (const QString& path);

};

#endif // DATAREADER_H
