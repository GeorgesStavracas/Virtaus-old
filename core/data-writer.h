#ifndef DATAWRITER_H
#define DATAWRITER_H

#include <QtCore>
#include <QtXml>
#include "core/collection.h"
#include "core/data-reader.h"
#include "core/settings.h"

namespace Virtaus {
    namespace Core {
        class DataWriter;
    }
}

class Virtaus::Core::DataWriter : public QObject
{

    Q_OBJECT

public:
    explicit DataWriter();

    /* Saving methods */
    bool saveAttribute(Virtaus::Core::Attribute* attribute);
    bool saveCategory(Virtaus::Core::Category* category);
    bool saveCollection(Virtaus::Core::Collection* collection);
    bool saveCollectionInfo(Virtaus::Core::Collection* collection);
    bool saveItem(Virtaus::Core::Item* item);

    /* Creation methods */
    bool createAttribute(Virtaus::Core::Attribute* attribute);
    bool createCategory(Virtaus::Core::Category* category);
    bool createCollection(Virtaus::Core::Collection* collection);
    bool createItem(Virtaus::Core::Item* item);

    /* Appending methods */
    bool appendSet(Virtaus::Core::Set* set);
    bool appendProduct(Virtaus::Core::Product* product);

    /* Deletion methods */
    bool removeAttibute(Virtaus::Core::Attribute* attribute);
    bool removeCategory(Virtaus::Core::Category* category);
    bool removeCollection(Virtaus::Core::Collection* collection);
    bool removeItem(Virtaus::Core::Item* item);
    bool removeSet(Virtaus::Core::Set* set);
    bool removeProduct(Virtaus::Core::Product* product);

signals:
    void fileCreated(QString file);
    void fileRemoved(QString file);
    void fileUpdated(QString file);
};

#endif // DATAWRITER_H
