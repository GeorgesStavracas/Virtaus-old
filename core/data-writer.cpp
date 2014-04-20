#include "data-writer.h"

using namespace Virtaus::Core;

DataWriter::DataWriter()
{
}

bool
DataWriter::saveItem(Virtaus::Core::Item* item)
{
    if (!item->getParent())
        return false;

    qDebug() << "Saving to " << item->getPath();

    /* Validate attribute */
    DataReader* reader = new DataReader;
    bool valid = reader->validateAttribute(item->getPath());

    /*
     * Since the attribute was previouly validated,
     * most of the validating code (such as checking
     * files existance, validating xml, etc) is not
     * needed. The validating algorithm is pretty much
     * efficient.
     */
    if (valid) {
        QFile* file = new QFile(item->getParent()->getPath() + "/Attribute.xml");
        file->open(QIODevice::ReadOnly | QIODevice::Text);

        QDomDocument* xml = new QDomDocument(item->getParent()->getPath() + "/Attribute.xml");
        xml->setContent(file);

        /* File was readed, close until update */
        file->close();

        /*
         * If current item exists, update it. If not,
         * create a new node.
         */
        bool has_item = reader->hasItem(item->getParent()->getPath(), item->getName());

        if (!has_item) {
            Settings* settings = Virtaus::Core::Settings::getInstance();

            QDomElement itemElement = xml->createElement("draw");

            QString format = settings->get("image-extension", ".png").toString();

            itemElement.setAttribute("name", item->getName());

            xml->documentElement().appendChild(itemElement);

            /* Write back to the file */
            if (file->open(QIODevice::WriteOnly | QIODevice::Truncate)) {
                QByteArray array = xml->toByteArray();
                file->write(array);

                //emit fileUpdated(file->???);

                file->close();
            }
            else
                valid = false;

        }
        else
            valid = false;

        delete file;
        delete xml;
    }

    delete reader;

    if (!valid)
        return false;

    return true;
}

bool
DataWriter::createCollection(Collection *collection)
{
    if (!collection)
        return false;

    qDebug() << "Creating collection" << collection->getInfo("name");
    qDebug() << "path: " << collection->getInfo("path");

    QString path = collection->getInfo("path");
    bool valid = true;

    QDir *dir = new QDir(path);

    /* Try to create the dir tree, and check if it was successful */
    if (!dir->exists())
    {
        if (!dir->mkpath(dir->absolutePath()))
        {
            delete dir;
            return false;
        }

        emit fileCreated(dir->absolutePath());
    }

    /* Directory already exists */
    else
    {
        delete dir;
        return false;
    }

    /*
     * Two-step proccess:
     * 1) Create Collection.xml with user-given data
     * 2) Create content-empty Info.xml
     */
    QFile* collection_xml = new QFile(dir->absolutePath() + "/Collection.xml");
    valid = collection_xml->open(QIODevice::WriteOnly | QIODevice::Truncate);

    QString xml = QString("<?xml version='1.0' encoding='UTF-8' ?>\n");

    /* TODO: get width and height from Settings */
    xml.append("<collection name=\"");
    xml.append(collection->getInfo("name"));
    xml.append("\" width=\"1920\" height=\"1080\">\n");

    xml.append("\t<author>");
    xml.append(collection->getInfo("author"));
    xml.append("</author>\n");

    xml.append("\t<email>");
    xml.append(collection->getInfo("email"));
    xml.append("</email>\n");

    xml.append("</collection>");

    collection_xml->write(xml.toUtf8());
    collection_xml->close();
    delete collection_xml;
    emit fileCreated(dir->absolutePath() + "/Collection.xml");


    QFile* info_xml = new QFile(dir->absolutePath() + "/Info.xml");
    valid = info_xml->open(QIODevice::WriteOnly | QIODevice::Truncate);

    xml = QString("<?xml version='1.0' encoding='UTF-8' ?>\n<info>\n</info>");

    info_xml->write(xml.toUtf8());
    info_xml->close();
    delete info_xml;
    emit fileCreated(dir->absolutePath() + "/Info.xml");

    return true;
}
