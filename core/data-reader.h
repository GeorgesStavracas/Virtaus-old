#ifndef DATAREADER_H
#define DATAREADER_H

#include <QtCore>
#include <QLinkedList>
#include <QXmlStreamReader>
#include <QtWidgets>
#include "collection.h"

namespace Virtaus {
    namespace Core {
        class DataReader;
    }
}

class Virtaus::Core::DataReader :
        public QObject
{

    Q_OBJECT

public:
        DataReader();

        QList<Virtaus::Core::Collection*>* loadData(const QString& path);

        /* Validating methods */
        bool validateAttribute(const QString& path);
        bool validateCategory(const QString& path);
        bool validateCollection(const QString& path);

        /* Auxiliary methods */
        bool hasItem (const QString& path, const QString& item);
        bool hasProduct (const QString& path, const QString& product);

        /* Loading methods */
        Virtaus::Core::Attribute* loadAttribute (const QString& path, Virtaus::Core::Category* parent);
        Virtaus::Core::Category* loadCategory (const QString& path, Virtaus::Core::Collection* parent);
        Virtaus::Core::Collection* loadCollection (const QString& path);
        bool loadCollectionInfo(Virtaus::Core::Collection* collection);

};

#endif // DATAREADER_H
