#include "data-reader.h"
#include <iostream>

using namespace Virtaus;

DataReader::DataReader() : QObject()
{
    QDir dir(QDir::homePath()+"/"+QObject::tr("My Collections"));

    if (!dir.exists())
        dir.mkdir(dir.absolutePath());

    this->dir = new QString(dir.absolutePath());
}

void
DataReader::setDir(const QString& dir)
{
    this->dir->clear();
    this->dir->append(dir);

}


/*
 * DataReader::validateAttribute(QString&)
 *
 * Validate a given path as an Attribute. This is achieved with
 * the following steps:
 * 1) Check for Attribute.xml and
 * 2) Check if the draws are valid
 */
bool
DataReader::validateAttribute(const QString &path)
{
    QFile *file = new QFile (path + "/Attribute.xml");

    if (!file->exists()) {
        delete file;
        return false;
    }

    file->open(QIODevice::ReadOnly | QIODevice::Text);

    QXmlStreamReader xml(file);

    /* Parse the XML file */
    while (!xml.atEnd() && !xml.hasError()) {

        /* Read the next element */
        QXmlStreamReader::TokenType token = xml.readNext();

        /* Parse the doc data */
        if (token == QXmlStreamReader::StartElement) {


            /* File contains invalid tags */
            if (xml.name() != "attribute" &&
                xml.name() != "draw")
            {
                delete file;
                return false;
            }

            if (xml.name() == "draw") {
                QXmlStreamAttributes attribs = xml.attributes();

                /* Load the item with the category 'c' as parent */
                if (attribs.hasAttribute("name")) {

                    QFile *img = new QFile (path + "/" + attribs.value("name").toString());

                    if (!img->exists()) {
                        delete img;
                        delete file;
                        return false;
                    }

                    delete img;
                }
            }
        }
    }

    xml.clear();

    delete file;

    if (xml.hasError())
        return false;

    return true;
}

/*
 * DataReader::validateCategory(QString&)
 *
 * Validate a given path as a Category. This is achieved with
 * the following steps:
 * 1) Check for Category.xml
 * 2) Check if the Attributes are valid
 * 3) Check if Products are valid
 */
bool
DataReader::validateCategory(const QString &path)
{
    QFile *file = new QFile (path + "/Category.xml");

    if (!file->exists()) {
        delete file;
        return false;
    }

    file->open(QIODevice::ReadOnly | QIODevice::Text);

    QXmlStreamReader xml(file);

    /* Parse the XML file */
    while (!xml.atEnd() && !xml.hasError()) {
        /* Read the next element */
        QXmlStreamReader::TokenType token = xml.readNext();

        /* Parse the doc data */
        if (token == QXmlStreamReader::StartElement) {


            /* File contains invalid tags */
            if (xml.name() != "category" &&
                xml.name() != "attribute" &&
                xml.name() != "products" &&
                xml.name() != "product" &&
                xml.name() != "item")
            {
                delete file;
                return false;
            }

            /* Check if the category has position and size fields */
            if (xml.name() == "category") {
                QXmlStreamAttributes attribs = xml.attributes();

                if (!attribs.hasAttribute("x") ||
                    !attribs.hasAttribute("y") ||
                    !attribs.hasAttribute("width") ||
                    !attribs.hasAttribute("height"))
                {
                    delete file;
                    return false;
                }
            }

            /* Check if the attributes are valid */
            if (xml.name() == "attribute") {
                QXmlStreamAttributes attribs = xml.attributes();

                /* Load the attribute with the category 'c' as parent */
                if (attribs.hasAttribute("name")) {

                    QDir *attrib = new QDir (path + "/" + attribs.value("name").toString());

                    bool attrib_valid = validateAttribute(attrib->absolutePath());

                    delete attrib;

                    if (!attrib_valid) {
                        delete file;
                        return false;
                    }

                }
            } // if (name == "attribute)

            /*
             * Validate products using DataReader::hasItem(path)
             * auxiliary method.
             */
            if (xml.name() == "products") {

               while (!(xml.tokenType() == QXmlStreamReader::EndElement &&
                        xml.name() == "products"))
               {

                   if (xml.tokenType() == QXmlStreamReader::StartElement &&
                           xml.name() == "item")
                   {
                       QXmlStreamAttributes attribs = xml.attributes();

                       if (attribs.hasAttribute("name") &&
                           attribs.hasAttribute("attribute"))
                       {

                           QString attrib_path = path + "/" + attribs.value("attribute").toString();

                           if (!hasItem(attrib_path, attribs.value("name").toString())) {
                               delete file;
                               return false;
                           } // if has item
                       } // if attribs
                       else {
                           delete file;
                           return false;
                       }
                   } // if item

                   xml.readNext();
               }

            }
        }
    }

    xml.clear();

    delete file;

    if (xml.hasError())
        return false;

    return true;
}

/*
 * DataReader::validateCollection(const QString &path)
 *
 * TODO: validate Sets
 */
bool
DataReader::validateCollection(const QString &path)
{
    bool collection_xml;
    bool info_xml;
    QDir* dir;
    QStringList entries;

    collection_xml = false;
    info_xml = false;
    dir = new QDir (path);
    entries = dir->entryList(QDir::Files);

    foreach (const QString& str, entries)
    {
        /* Parse collection main data */
        if (str == "Collection.xml")
        {
            QFile *file = new QFile(path + "/" + str);
            file->open(QIODevice::ReadOnly | QIODevice::Text);

            QXmlStreamReader xml(file);

            while (!xml.atEnd() && !xml.hasError()) {

                if (xml.tokenType() == QXmlStreamReader::StartElement) {

                    /* File contains invalid tags */
                    if (xml.name() != "collection" &&
                        xml.name() != "categories" &&
                        xml.name() != "category" &&
                        xml.name() != "sets" &&
                        xml.name() != "set" &&
                        xml.name() != "product" &&
                        xml.name() != "author" &&
                        xml.name() != "email")
                    {
                        delete file;
                        return false;
                    }

                    /* Parse CATEGORIES first */
                    if (xml.name().toString() == "categories") {

                        while (!(xml.tokenType() == QXmlStreamReader::EndElement &&
                               xml.name() == "categories")) {

                            /* Parse <category> tag */
                            if (xml.tokenType() == QXmlStreamReader::StartElement &&
                                xml.name() == "category")
                            {

                                /* Load info from the attribute 'name' */
                                QXmlStreamAttributes attribs = xml.attributes();

                                if (attribs.hasAttribute("name")) {

                                    /* Try to enter the directory */
                                    dir->cd(attribs.value("name").toString());

                                    /* Check the directory */
                                    if (dir->exists() &&
                                        this->validateCategory(dir->absolutePath()))
                                    {
                                        collection_xml = true;
                                    }

                                    else
                                    {
                                        /*
                                         * The code bruptly ends here when the collection
                                         * is not valid in order to avoid unnecessary
                                         * iteration.
                                         */
                                        delete file;
                                        delete dir;
                                        return false;
                                    }

                                    /* Return to the previous directory */
                                    dir->cdUp();
                                }
                            } //if

                            xml.readNext();
                        }

                    } // if (name == "categories")


                    if (xml.name().toString() == "product") {
                        QXmlStreamAttributes attribs = xml.attributes();

                        if (attribs.hasAttribute("name") &&
                            attribs.hasAttribute("category"))
                        {

                            QString prod_path = path + "/" + attribs.value("category").toString();

                            if (!hasProduct(prod_path, attribs.value("name").toString())) {
                                delete file;
                                return false;
                            }
                        }

                        else {
                            delete file;
                            return false;
                        }
                    }
                }

                xml.readNext();

            } // While

            xml.clear();

            if (xml.hasError())
                collection_xml = false;

            delete file;
        }

        /* Parse collection secondary data */
        if (str == "Info.xml")
        {
            info_xml = true;

        }

    }

    delete dir;

    return info_xml && collection_xml;
}

bool
DataReader::hasItem(const QString& path, const QString& item)
{
    QFile *file = new QFile (path + "/Attribute.xml");

    /*
     * File must exist AND the attribute (it must be an
     * attribute dir) must be valid.
     */
    if (!(file->exists() && validateAttribute(path))) {
        delete file;
        return false;
    }

    file->open(QIODevice::ReadOnly | QIODevice::Text);

    QXmlStreamReader xml(file);

    /* Parse the XML file */
    while (!xml.atEnd() && !xml.hasError()) {
        /* Read the next element */
        QXmlStreamReader::TokenType token = xml.readNext();

        /* Parse the doc data */
        if (token == QXmlStreamReader::StartElement) {
            if (xml.name() == "draw") {
                QXmlStreamAttributes attribs = xml.attributes();

                /* Load the item with the category 'c' as parent */
                if (attribs.hasAttribute("name")) {

                    if (attribs.value("name").toString() != item)
                        continue;

                    QFile *img = new QFile (path + "/" + item);

                    if (img->exists()) {
                        delete img;
                        delete file;
                        return true;
                    }

                    delete img;

                }
            }
        }

    }

    return false;
}

bool
DataReader::hasProduct (const QString& path, const QString& product)
{
    QFile *file = new QFile (path + "/Category.xml");

    if (!(file->exists() && validateCategory(path))) {
        delete file;
        return false;
    }

    file->open(QIODevice::ReadOnly | QIODevice::Text);

    QXmlStreamReader xml(file);

    /* Parse the XML file */
    while (!xml.atEnd() && !xml.hasError()) {
        /* Read the next element */
        QXmlStreamReader::TokenType token = xml.readNext();

        /* Parse the doc data */
        if (token == QXmlStreamReader::StartElement) {

            /*
             * Search for products.
             */
            if (xml.name() == "products") {

               while (!(xml.tokenType() == QXmlStreamReader::EndElement &&
                        xml.name() == "products"))
               {

                   if (xml.tokenType() == QXmlStreamReader::StartElement &&
                           xml.name() == "product")
                   {
                       QXmlStreamAttributes attribs = xml.attributes();

                       if (attribs.hasAttribute("name"))
                       {
                           if (attribs.value("name").toString() == product) {
                               delete file;
                               return true;
                           }

                       } // if attribs
                   } // if item

                   xml.readNext();
               }

            }
        }
    }

    xml.clear();

    delete file;

    return false;
}


/*
 * At the given path, load recursively
 * All the valid collections
 */
QList<Virtaus::Collection*>*
DataReader::loadData()
{
    qDebug() << "Loading data...\n";
    QDir *dir = new QDir(*this->dir);
    QList<Virtaus::Collection*> *list = new QList<Virtaus::Collection*>;

    foreach (const QString& path, dir->entryList(QDir::Dirs)) {
        QDir *aux = new QDir(*dir);
        aux->cd(path);

        qDebug() << "Validating collection at path '" << aux->absolutePath() << "'";
        if (this->validateCollection(aux->absolutePath())) {
            qDebug() << "Valid collection.\n";
            //Collection* c = this->loadCollection(aux->absolutePath());
            //list->append(c);
        } else {
            qDebug() << "Invalid collection.\n";
        }

        delete aux;
    }

    delete dir;

    return list;
}

/*
 * Load a single collection from the given path
 */
Virtaus::Collection*
DataReader::loadCollection (const QString& path) {

    Collection* collection = new Collection;

    collection->setInfo("path", path);

    /* Load the thumbnail */
    QFile *file = new QFile (path + "/thumbnail.png");

    if (file->exists())
        collection->thumbnail = new QString(path + "/thumbnail.png");
    else
        collection->thumbnail = new QString(":/virtaus/images/resources/no_thumbnail.svg");

    delete file;

    /*
     * This is safe because this method is only called
     * for valid directories
     */
    file = new QFile(path + "/Collection.xml");
    file->open(QIODevice::ReadOnly | QIODevice::Text);

    QXmlStreamReader xml(file);

    /* Parse the XML file, token by token */
    while (!xml.atEnd() && !xml.hasError()) {

        /* Read the next element */
        QXmlStreamReader::TokenType token = xml.readNext();

        /* If it's the start of document, we can skip safely */
        if (token == QXmlStreamReader::StartDocument)
            continue;

        /* Parse the doc data */
        if (token == QXmlStreamReader::StartElement) {

            /* Ge the collection name */
            if (xml.name() == "collection") {

                QXmlStreamAttributes attribs = xml.attributes();

                if (attribs.hasAttribute("name"))
                    collection->setInfo ("name", attribs.value("name").toString());

            }

            if (xml.name() == "author") {
                xml.readNext();

                if (xml.tokenType() == QXmlStreamReader::Characters)
                    collection->setInfo("author", xml.text().toString());

            }

            if (xml.name() == "email") {
                xml.readNext();

                if (xml.tokenType() == QXmlStreamReader::Characters)
                    collection->setInfo("email", xml.text().toString());

            }

            if (xml.name() == "categories") {

                while (!(xml.tokenType() == QXmlStreamReader::EndElement &&
                       xml.name() == "categories"))
                {

                    token = xml.readNext();

                    if (token == QXmlStreamReader::StartElement &&
                            xml.name() == "category")
                    {
                        QXmlStreamAttributes attribs = xml.attributes();

                        if (attribs.hasAttribute("name")){}
                            //collection->getCategories()->append(attribs.value("name").toString());


                    }

                }

            }
        }

    }

    /* Parsing error */
    if (xml.hasError()) {
        delete collection;
        collection = NULL;
    }

    xml.clear();

    delete file;

    return collection;
}

/*
 * Load a single category for the given path
 */
Virtaus::Category*
DataReader::loadCategory (const QString &path, Collection *parent)
{
    QDir *dir = new QDir(path);
    Category* c = new Virtaus::Category(parent);

    QFile *file = new QFile(path + "/Category.xml");

    if (!file->exists()) {
        delete dir;
        delete c;
        return NULL;
    }

    file->open(QIODevice::ReadOnly | QIODevice::Text);

    QXmlStreamReader xml(file);

    /* Parse the XML file, token by token */
    while (!xml.atEnd() && !xml.hasError()) {

        /* Read the next element */
        QXmlStreamReader::TokenType token = xml.readNext();

        /* If it's the start of document, we can skip safely */
        if (token == QXmlStreamReader::StartDocument)
            continue;

        /* Parse the doc data */
        if (token == QXmlStreamReader::StartElement) {

            /*
             * Load fields {x, y, width, height} from <category>
             */
            if (xml.name() == "category") {

                QXmlStreamAttributes attribs = xml.attributes();

                if (attribs.hasAttribute("x"))
                    c->getPoint()->setX(attribs.value("x").toString().toInt());

                if (attribs.hasAttribute("y"))
                    c->getPoint()->setY(attribs.value("y").toString().toInt());

                if (attribs.hasAttribute("width"))
                    c->getSize()->setWidth(attribs.value("width").toString().toInt());

                if (attribs.hasAttribute("height"))
                    c->getSize()->setHeight(attribs.value("height").toString().toInt());
            }

            /*
             * TODO: finish Category loading.
             *
             * Missing:
             * - Attribute loading
             * - Product loading
             */
        }
    }

    delete dir;
    delete file;

    return c;
}

QString*
DataReader::getDir () {
    return this->dir;
}
