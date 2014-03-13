#ifndef COLLECTION_H
#define COLLECTION_H

#include <QMap>
#include <QtCore>
#include <QtGui>
#include <QString>

namespace Virtaus {
    class Attribute;
    class Category;
    class Collection;
    class Item;
    class Product;
    class Set;
}

/*
 * Class definitions
 */

class Virtaus::Attribute {
public:
    explicit Attribute();

    QString* getName();
    QList<Virtaus::Item>* getItemList();
    Virtaus::Category* getParent();
    QString& getPath();
    int getZIndex();

    void setName(QString& name);
    void setParent(Category* parent);
    void setZIndex (int index);

protected:
    QString* name;
    QList<Virtaus::Item>* itemlist;
    Virtaus::Category* parent;
    int z_index;
};

class Virtaus::Category
{
public:
    explicit Category();

    QString* getName();
    QPoint* getPoint();
    QSize* getSize();
    QList<Virtaus::Attribute>* getAttributeList();
    QList<Virtaus::Product>* getProductList();
    Virtaus::Collection* getParent();
    QString& getPath();

    void setParent (Virtaus::Collection* parent);
    void setName (const QString name);
    void setPoint (QPoint* point);
    void setSize (QSize* size);

protected:
    QString* name;
    QPoint* point;
    QSize* size;
    Virtaus::Collection* parent;
    QList<Virtaus::Attribute>* attribs;
    QList<Virtaus::Product>* products;
};

class Virtaus::Collection
{
public:
    Collection();

    QString getInfo (QString field = "");

    void setInfo (QString key, QString value);
    QLinkedList<Virtaus::Category>* getCategories();
    QString* thumbnail;
private:
    QMap<QString, QString> *info;
    QLinkedList<Virtaus::Category> *categories;
};

class Virtaus::Item
{
public:
    Item(Virtaus::Category* parent);

    QImage* getImage();
    QString* getName();
    Virtaus::Category* getParent();
    QString& getPath();

    void setImage (const QString& path);
    void setName (const QString& name);

protected:
    QString* name;
    QImage* image;
    Virtaus::Category* parent;
};

class Virtaus::Product
{
public:
    Product(const Virtaus::Collection *parent);

    QString* getName();
    QList<Virtaus::Item>* getItemList();
    const Virtaus::Collection* getParent();

    void setName (const QString& name);

private:
    QString *name;
    QList<Virtaus::Item> *items;
    const Virtaus::Collection* parent;
};

class Virtaus::Set
{
public:
    explicit Set (Virtaus::Collection *parent);

    QString* getName();
    QList<Virtaus::Product>* getProductList();
    Virtaus::Collection* getParent();

    void setName (const QString& name);

protected:
    QString* name;
    QList<Virtaus::Product>* products;
    Virtaus::Collection* parent;
};

#endif // COLLECTION_H
