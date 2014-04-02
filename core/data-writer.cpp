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


            QString format = QString(settings->get<std::string>(QString("image-extension")));


            itemElement.setAttribute("name", item->getName());

            xml->documentElement().appendChild(itemElement);

            /* Write back to the file */
            if (file->open(QIODevice::WriteOnly | QIODevice::Truncate)) {
                QByteArray array = xml->toByteArray();
                file->write(array);
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
