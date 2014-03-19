#ifndef COLLECTION_H
#define COLLECTION_H

#include <QMap>
#include <QString>
#include <QtCore>
#include <QtGui>
#include <QObject>

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

class Virtaus::Attribute : public QObject
{

    Q_OBJECT

public:
    explicit Attribute(Virtaus::Category* parent);
    ~Attribute();

    QString* getName();
    QMap<QString, Virtaus::Item*>* getItemList();
    Virtaus::Category* getParent();
    QString& getPath();
    int getZIndex();

    void setName(QString& name);
    void setZIndex (int index);

protected:
    QString* name;
    QMap<QString, Virtaus::Item*>* itemlist;
    Virtaus::Category* parent;
    int z_index;
};

class Virtaus::Category : public QObject
{
public:
    explicit Category(Virtaus::Collection* parent);
    ~Category();

    QString* getName();
    QPoint* getPoint();
    QSize* getSize();
    QMap<QString, Virtaus::Attribute*>* getAttributeList();
    QMap<QString, Virtaus::Product*>* getProductList();
    Virtaus::Collection* getParent();
    QString& getPath();

    void setName (const QString name);
    void setPoint (QPoint* point);
    void setSize (QSize* size);

protected:
    QString* name;
    QPoint* point;
    QSize* size;
    Virtaus::Collection* parent;
    QMap<QString, Virtaus::Attribute*>* attribs;
    QMap<QString, Virtaus::Product*>* products;
};

class Virtaus::Collection : public QObject
{
public:
    explicit Collection();
    ~Collection();

    QString getInfo (QString field = "");

    void setInfo (QString key, QString value);
    QMap<QString, Virtaus::Category*>* getCategories();
    QString* thumbnail;
private:
    QMap<QString, QString> *info;
    QMap<QString, Virtaus::Category*> *categories;
};

class Virtaus::Item : public QObject
{
public:
    Item(Virtaus::Attribute* parent);
    ~Item();

    QImage* getImage();
    QString* getName();
    Virtaus::Attribute* getParent();
    QString& getPath();

    void setImage (const QString& path);
    void setName (const QString& name);

protected:
    QString* name;
    QImage* image;
    QString* image_path;
    Virtaus::Attribute* parent;
};

class Virtaus::Product : public QObject
{
public:
    Product(const Virtaus::Collection *parent);

    QString* getName();
    QMap<QString, Virtaus::Item*>* getItemList();
    const Virtaus::Collection* getParent();

    void setName (const QString& name);

private:
    QString *name;
    QMap<QString, Virtaus::Item*> *items;
    const Virtaus::Collection* parent;
};

class Virtaus::Set : public QObject
{
public:
    explicit Set (Virtaus::Collection *parent);

    QString* getName();
    QMap<QString, Virtaus::Product*>* getProductList();
    Virtaus::Collection* getParent();

    void setName (const QString& name);

protected:
    QString* name;
    QMap<QString, Virtaus::Product*>* products;
    Virtaus::Collection* parent;
};

#endif // COLLECTION_H
