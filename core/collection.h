#ifndef COLLECTION_H
#define COLLECTION_H

#include <QMap>
#include <QtCore>
#include <QtGui>
#include <QString>

namespace Virtaus {
    class Collection;
    class Category;
    class Item;
    class Product;
}

/*
 * Class definitions
 */
class Virtaus::Collection
{
public:
    Collection();

    QString getInfo (QString field = "");

    void setInfo (QString key, QString value);
    QLinkedList<QString>* getCategories();
    QString* thumbnail;
private:
    QMap<QString, QString> *info;
    QLinkedList<QString> *categories;
};


class Virtaus::Category
{
public:
    Category();

    QString* getName();
    QPoint* getPoint();
    QSize* getSize();
    QList<QString>* getItemList();
    Virtaus::Collection* getParent();

    void setParent (Virtaus::Collection* parent);
    void setName (const QString name);
    void setPoint (QPoint* point);
    void setSize (QSize* size);

protected:
    QString* name;
    QPoint* point;
    QSize* size;
    Virtaus::Collection* parent;
    QList<QString>* itemlist;
};

class Virtaus::Item
{
public:
    Item(Virtaus::Category* parent);

    QImage* getImage();
    QString* getName();
    Virtaus::Category* getParent();

    void setImage (const QString& path);
    void setName (const QString& name);

protected:
    QString* name;
    QImage* image;
    const Virtaus::Category* parent;
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

#endif // COLLECTION_H
