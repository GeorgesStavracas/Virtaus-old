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

    std::cout << "Directory: " << dir.toStdString() << "\n";
}

bool
DataReader::isValidPath (const QString& path) {
    QDir* dir = new QDir (path);
    bool collection_xml = false, info_xml = false;
    QStringList entries = dir->entryList(QDir::Files);


    foreach (const QString& str, entries) {
        if (str == "Collection.xml")
            collection_xml = true;

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
QLinkedList<Virtaus::Collection>*
DataReader::loadData() {
    QDir *dir = new QDir(*this->dir);
    QLinkedList<Virtaus::Collection> *list = new QLinkedList<Virtaus::Collection>;

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

    /*
     * This is safe because this method is only called
     * for valid directories
     */
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

            /*
             * Load the categories
             */
            if (xml.name() == "categories") {

                while (!(xml.tokenType() == QXmlStreamReader::EndElement &&
                         xml.name() == "categories")) {

                    if (xml.tokenType() == QXmlStreamReader::StartElement) {

                        if (xml.name() == "category") {

                            /* Load info from the attribute 'name' */
                            QXmlStreamAttributes attribs = xml.attributes();

                            if (attribs.hasAttribute("name")) {
                                QString category_path = path + "/" + attribs.value("name").toString();

                                Virtaus::Category *category = this->loadCategory(category_path);

                                if (!category)
                                    continue;

                                category->setParent(collection);
                                category->setName(attribs.value("name").toString());

                                collection->getCategories()->append(*category);

                            }

                        } //if - name
                    } //if - token

                    xml.readNext();

                } //while
            } //if - name


            /*
             * Load products
             */
            if (xml.name() == "product") {

                /* Load info from the attribute 'name' */
                QXmlStreamAttributes attribs = xml.attributes();

                if (!attribs.hasAttribute("name"))
                    continue;

                /* Load data at product */
                Virtaus::Product *product = new Virtaus::Product(collection);
                product->setName(attribs.value("name").toString());

                /* Load the items of the product */
                while (!(xml.tokenType() == QXmlStreamReader::EndElement &&
                         xml.name() == "product")) {

                    if (xml.tokenType() == QXmlStreamReader::StartElement &&
                            xml.name() == "item") {

                        attribs = xml.attributes();

                        // Load fields 'category' and 'name'
                        QString name = attribs.value("name").toString();
                        QString item_category = attribs.value("category").toString();

                        // Search for the category with the name
                        Virtaus::Category *aux = NULL;
                        foreach (Category aux2, *collection->getCategories()) {
                            if (aux2.getName() == item_category)
                                aux = &aux2;
                        }

                        // Error shield
                        if (!aux) {
                            delete product;
                            break;
                        }

                        // Search for the item at the category
                        Virtaus::Item *item = NULL;
                        foreach (Virtaus::Item item2, *aux->getItemList()) {
                            if (item2.getName() == name)
                                item = &item2;
                        }

                        // Error shield again
                        if (!item) {
                            delete product;
                            break;
                        }

                        product->getItemList()->append(*item);

                    } //if - token

                    xml.readNext();

                } // while
            }
        }

    }

    /* Parsing error */
    if (xml.hasError()) {
        delete collection;
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

    if (!file->exists())
        return NULL;

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

QString*
DataReader::getDir () {
    return this->dir;
}
