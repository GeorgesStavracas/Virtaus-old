#include "data-reader.h"
#include <iostream>

using namespace Virtaus;

DataReader::DataReader() : QObject()
{
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

    bool valid = true;

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

                    if (!img->exists())
                        valid = false;

                    delete img;
                }
                else
                    valid = false;
            }
        }

        if (!valid) {
            delete file;
            return false;
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

    bool valid = true;

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
                valid = false;
            }

            /* Check if the category has position and size fields */
            if (xml.name() == "category") {
                QXmlStreamAttributes attribs = xml.attributes();

                if (!attribs.hasAttribute("x") ||
                    !attribs.hasAttribute("y") ||
                    !attribs.hasAttribute("width") ||
                    !attribs.hasAttribute("height"))
                {
                    valid = false;
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

                    if (!attrib_valid)
                        valid = false;

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

                           if (!hasItem(attrib_path, attribs.value("name").toString()))
                               valid = false;

                       } // if attribs

                       else
                           valid = false;

                   } // if item

                   if (!valid) {
                       delete file;
                       return false;
                   }

                   xml.readNext();

               }

            }
        }

        if (!valid) {
            delete file;
            return false;
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

    bool valid = true;

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
                        file->close();
                        delete file;
                        return false;
                    }

                    if (xml.name().toString() == "collection") {
                        QXmlStreamAttributes attribs = xml.attributes();

                        if (!(attribs.hasAttribute("width") &&
                              attribs.hasAttribute("height")))
                        {
                            valid = false;
                        }
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
                                        valid = false;

                                    /* Return to the previous directory */
                                    dir->cdUp();
                                } else
                                    valid = false;
                            } //if

                            if (!valid) {
                                file->close();
                                delete file;
                                return false;
                            }

                            xml.readNext();
                        }

                    } // if (name == "categories")


                    if (xml.name().toString() == "product") {
                        QXmlStreamAttributes attribs = xml.attributes();

                        if (attribs.hasAttribute("name") &&
                            attribs.hasAttribute("category"))
                        {

                            QString prod_path = path + "/" + attribs.value("category").toString();

                            if (!hasProduct(prod_path, attribs.value("name").toString()))
                                valid = false;
                        }

                        else
                            valid = false;
                    }
                }

                if (!valid) {
                    file->close();
                    delete file;
                    return false;
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
DataReader::loadData(const QString& path)
{
    qDebug() << "Loading data...\n";
    QDir *dir = new QDir(path);
    QList<Virtaus::Collection*> *list = new QList<Virtaus::Collection*>;

    foreach (const QString& subdir, dir->entryList(QDir::NoDotAndDotDot | QDir::Dirs)) {
        dir->cd(subdir);

        qDebug() << "Validating collection at path '" << dir->absolutePath() << "'";
        if (this->validateCollection(dir->absolutePath())) {
            qDebug() << "Valid collection.\n";
            Collection* c = this->loadCollection(dir->absolutePath());
            list->append(c);
        } else {
            qDebug() << "Invalid collection.\n";
        }

        dir->cd(path);
    }

    delete dir;

    return list;
}

Virtaus::Attribute*
DataReader::loadAttribute (const QString& path, Virtaus::Category* parent)
{
    QDir *dir = new QDir(path);
    Attribute* att = new Virtaus::Attribute(parent);

    QFile *file = new QFile(path + "/Attribute.xml");

    if (!file->exists()) {
        delete dir;
        delete att;
        return NULL;
    }

    file->open(QIODevice::ReadOnly | QIODevice::Text);

    QXmlStreamReader xml(file);

    /* Parse the XML file, token by token */
    while (!xml.atEnd() && !xml.hasError()) {

        /* Read the next element */
        QXmlStreamReader::TokenType token = xml.readNext();

        if (token == QXmlStreamReader::StartElement) {

            /* Load the item */
            if (xml.name() == "draw") {

                QXmlStreamAttributes attribs = xml.attributes();

                QFileInfo* info = new QFileInfo(path + "/" + attribs.value("name").toString());

                Virtaus::Item* item = new Virtaus::Item(att);
                item->setName(info->baseName());
                item->setFilename(info->fileName());
                item->setImage(info->absoluteFilePath());

                att->getItemList()->insert(info->baseName(), item);
            }

        }

    }

    return att;
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

            /* Load attributes */
            if (xml.name() == "attribute") {

                QXmlStreamAttributes attribs = xml.attributes();

                if (attribs.hasAttribute("name")) {

                    QString attrib_name = attribs.value("name").toString();

                    /* Load the corresponding attribute */
                    Attribute* attrib = loadAttribute(path + "/" + attrib_name, c);
                    attrib->setName(attrib_name);

                    c->getAttributeList()->insert(attrib_name, attrib);
                }
            }

            /* Load products */
            if (xml.name() == "product") {

                Virtaus::Product* product = new Virtaus::Product(c);

                QXmlStreamAttributes attribs = xml.attributes();

                /* Only load products with name */
                if (attribs.hasAttribute("name"))
                    product->setName(attribs.value("name").toString());
                else {
                    delete product;
                    continue;
                }

                while (!(xml.tokenType() == QXmlStreamReader::EndElement &&
                         xml.name() == "product"))
                {
                    if (xml.tokenType() == QXmlStreamReader::StartElement &&
                            xml.name() == "item")
                    {
                        QXmlStreamAttributes attrs = xml.attributes();

                        QString name = attrs.value("name").toString();
                        QString attribute = attrs.value("attribute").toString();

                        if (!hasItem(path+"/"+attribute, name)) {
                            delete product;
                            product = NULL;
                            break;
                        }

                        if (!c->getAttributeList()->contains(attribute)) {
                            delete product;
                            product = NULL;
                            break;
                        }

                        Attribute* attrib_data = c->getAttributeList()->value(attribute);
                        Virtaus::Item* item = attrib_data->getItemList()->value(name);

                        /* Product name is '[Attribute]/[Item]' */
                        product->getItemList()->insert(attribute+"/"+name, item);

                    }

                    xml.readNext();
                }

                /* Only add to the list when the product actually exists */
                if (product)
                    c->getProductList()->insert(*product->getName(), product);

            }

        }
    }

    delete dir;
    delete file;

    return c;
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

        /* Parse the doc data */
        if (token == QXmlStreamReader::StartElement) {

            /* Ge the collection name */
            if (xml.name() == "collection") {

                QXmlStreamAttributes attribs = xml.attributes();

                if (attribs.hasAttribute("name"))
                    collection->setInfo ("name", attribs.value("name").toString());

                if (attribs.hasAttribute("width"))
                    collection->setInfo("width", attribs.value("width").toString());

                if (attribs.hasAttribute("height"))
                    collection->setInfo("height", attribs.value("height").toString());
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

                        if (attribs.hasAttribute("name")){
                            QString c_name = attribs.value("name").toString();
                            QString c_path = path + "/" + c_name;

                            Category* category = loadCategory(c_path, collection);
                            category->setName(c_name);

                            collection->getCategories()->insert(c_name, category);
                        }
                    }
                }
            }

            /* Load Sets */
            if (xml.name() == "sets") {

                while (!(xml.tokenType() == QXmlStreamReader::EndElement &&
                         xml.name() == "sets"))
                {

                    /* Load a set */
                    if (xml.tokenType() == QXmlStreamReader::StartElement &&
                        xml.name() == "set")
                    {

                        QXmlStreamAttributes attribs = xml.attributes();

                        if (attribs.hasAttribute("name")){
                            Virtaus::Set* set = new Virtaus::Set(collection);
                            set->setName(attribs.value("name").toString());

                            while (!(xml.tokenType() == QXmlStreamReader::EndElement &&
                                     xml.name() == "set"))
                            {

                                if (xml.tokenType() == QXmlStreamReader::StartElement &&
                                    xml.name() == "product")
                                {
                                    QXmlStreamAttributes attribs2 = xml.attributes();

                                    QString p_name = attribs2.value("name").toString();
                                    QString p_catg = attribs2.value("category").toString();

                                    if (!collection->getCategories()->contains(p_catg)) {
                                        delete set;
                                        set = NULL;
                                        break;
                                    }

                                    Virtaus::Category* catg = collection->getCategories()->value(p_catg);

                                    if (!catg->getProductList()->contains(p_name)) {
                                        delete set;
                                        set = NULL;
                                        break;
                                    }

                                    Virtaus::Product* prod = catg->getProductList()->value(p_name);

                                    set->getProductList()->insert(p_catg+"/"+p_name, prod);
                                }


                                xml.readNext();
                            }

                            if (set)
                                collection->getSets()->insert(*set->getName(), set);

                        }
                    }

                    xml.readNext();
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
