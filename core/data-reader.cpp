#include "data-reader.h"
#include <iostream>

using namespace Virtaus;

DataReader::DataReader()
{
    QDir dir(QDir::homePath()+"/"+QObject::tr("My Collections"));

    if (!dir.exists())
        dir.mkdir(dir.absolutePath());

    this->dir = new QString(dir.absolutePath());
}

void
DataReader::setDir(const QString& dir){
    this->dir->clear();
    *this->dir = dir;

}

bool
DataReader::isValidPath (const QString& path) {
    QDir* dir = new QDir (path);
    bool collection_xml = false, info_xml = false;
    QStringList entries = dir->entryList(QDir::Files);


    foreach (const QString& str, entries) {
        if (str == "Collection.xml") {

            QFile *file = new QFile(path + "/Collection.xml");
            file->open(QIODevice::ReadOnly | QIODevice::Text);

            QXmlStreamReader xml(file);

            /* Parse the XML file, token by token */
            while (!xml.atEnd() && !xml.hasError()) {

                /* Read the next element */
                QXmlStreamReader::TokenType token = xml.readNext();

                /* If it's the start of document, we can skip safely */
                if (token == QXmlStreamReader::StartDocument)
                    continue;

                if (token == QXmlStreamReader::StartElement) {

                    if (xml.name().toString() == "categories") {

                        while (!(xml.tokenType() == QXmlStreamReader::EndElement &&
                                 xml.name() == "categories")) {

                            if (xml.tokenType() == QXmlStreamReader::StartElement) {

                                if (xml.name() == "category") {

                                    /* Load info from the attribute 'name' */
                                    QXmlStreamAttributes attribs = xml.attributes();

                                    if (attribs.hasAttribute("name")) {

                                        /* Try to enter the directory */
                                        dir->cd(attribs.value("name").toString());

                                        if (dir->exists() &&
                                            this->isValidCategory(dir->absolutePath()))
                                        {
                                            collection_xml = true;
                                        }

                                        else {
                                            delete file;
                                            delete dir;
                                            return false;
                                        }

                                        dir->cdUp();

                                    }

                                } //if - name
                            } //if - token

                            xml.readNext();
                        }

                    }

                    if (xml.name().toString() == "product") {

                        /* Parse the product */
                        while (!(xml.tokenType() == QXmlStreamReader::EndElement &&
                                 xml.name() == "product"))
                        {
                            if (xml.tokenType() == QXmlStreamReader::StartElement &&
                                xml.name() == "item")
                            {
                                QXmlStreamAttributes attribs = xml.attributes();

                                if (attribs.hasAttribute("name") ||
                                    attribs.hasAttribute("category")) {

                                    QFile *item = new QFile (path + "/" + attribs.value("category").toString()
                                                             + "/" + attribs.value("name").toString());

                                    if (!item->exists()) {
                                        delete item;
                                        delete file;
                                        delete dir;
                                        return false;
                                    }

                                    delete item;


                                } else {
                                    delete file;
                                    delete dir;
                                    return false;
                                }

                            }

                            xml.readNext();
                        }
                    }
                }
            }

            xml.clear();


            if (xml.hasError())
                collection_xml = false;

            delete file;

        }

        if (str == "Info.xml")
            info_xml = true;
    }

    delete dir;

    return info_xml && collection_xml;
}

/*
 * At the given path, load recursively
 * All the valid collections
 */
QList<Virtaus::Collection>*
DataReader::loadData() {
    QDir *dir = new QDir(*this->dir);
    QList<Virtaus::Collection> *list = new QList<Virtaus::Collection>;

    foreach (const QString& path, dir->entryList(QDir::Dirs)) {

        QDir *aux = new QDir (*dir);
        aux->cd(path);

        if (this->isValidPath(aux->absolutePath())) {
            Collection* c = this->loadCollection(aux->absolutePath());
            list->append(*c);
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

                    if (token == QXmlStreamReader::StartDocument &&
                            xml.name() == "categiry")
                    {
                        QXmlStreamAttributes attribs = xml.attributes();

                        if (attribs.hasAttribute("name"))
                            collection->getCategories()->append(attribs.value("name").toString());

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
DataReader::loadCategory (const QString& path) {
    QDir *dir = new QDir(path);
    Category* c = new Category;

    /*
     * FIXME: This is not safe. We MUST check for
     * Collection.xml existence before loading it.
     */
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
             * Load the items from <draw>
             */
            if (xml.name() == "draw") {

                QXmlStreamAttributes attribs = xml.attributes();

                /* Load the item with the category 'c' as parent */
                if (attribs.hasAttribute("name")) {

                    Virtaus::Item* item = new Virtaus::Item(c);

                    QFileInfo *info = new QFileInfo(path + "/" + attribs.value("name").toString());

                    item->setName(info->baseName());
                    item->setImage(path + "/" + attribs.value("name").toString());
                    c->addItem(item);

                    delete info;
                }

            }
        }
    }

    delete dir;
    delete file;

    return c;
}

/* Parse category data and validate it */
bool
DataReader::isValidCategory (const QString& path) {

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

        /* If it's the start of document, we can skip safely */
        if (token == QXmlStreamReader::StartDocument)
            continue;

        /* Parse the doc data */
        if (token == QXmlStreamReader::StartElement) {

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

QString*
DataReader::getDir () {
    return this->dir;
}
