#ifndef COLLECTION_H
#define COLLECTION_H

#include <QMap>
#include <QString>
#include <QtCore>
#include <QtGui>
#include <QObject>

namespace Virtaus {
    namespace Core {
        class Attribute;
        class Category;
        class Collection;
        class Item;
        class Product;
        class Set;
    }
}

/*
 * Class definitions
 */

class Virtaus::Core::Attribute : public QObject
{

    Q_OBJECT

public:
    explicit Attribute(Virtaus::Core::Category* parent);
    ~Attribute();

    QString* getName();
    QMap<QString, Virtaus::Core::Item*>* getItemList();
    Virtaus::Core::Category* getParent();
    QString& getPath();
    int getZIndex();

    void setName(QString& name);
    void setZIndex (int index);

protected:
    QString* name;
    QMap<QString, Virtaus::Core::Item*>* itemlist;
    Virtaus::Core::Category* parent;
    int z_index;
};

class Virtaus::Core::Category : public QObject
{
public:
    explicit Category(Virtaus::Core::Collection* parent);
    ~Category();

    QString* getName();
    QPoint* getPoint();
    QSize* getSize();
    QMap<QString, Virtaus::Core::Attribute*>* getAttributeList();
    QMap<QString, Virtaus::Core::Product*>* getProductList();
    Virtaus::Core::Collection* getParent();
    QString& getPath();

    void setName (const QString name);
    void setPoint (QPoint* point);
    void setSize (QSize* size);

protected:
    QString* name;
    QPoint* point;
    QSize* size;
    Virtaus::Core::Collection* parent;
    QMap<QString, Virtaus::Core::Attribute*>* attribs;
    QMap<QString, Virtaus::Core::Product*>* products;
};

class Virtaus::Core::Collection : public QObject
{
public:
    explicit Collection();
    ~Collection();

    QString getInfo (QString field = "");

    void setInfo (QString key, QString value);
    QMap<QString, Virtaus::Core::Category*>* getCategories();
    QMap<QString, Virtaus::Core::Set*>* getSets();
    QString* thumbnail;
private:
    QMap<QString, QString> *info;
    QMap<QString, Virtaus::Core::Category*> *categories;
    QMap<QString, Virtaus::Core::Set*> *sets;
};

class Virtaus::Core::Item : public QObject
{
public:
    Item(Virtaus::Core::Attribute* parent);
    ~Item();

    QString& getFilename();
    QImage* getImage();
    QString& getName();
    Virtaus::Core::Attribute* getParent();
    QString& getPath();

    void setFilename (const QString& name);
    void setImage (const QString& path);
    void setName (const QString& name);

protected:
    QString* name;
    QString* filename;
    QImage* image;
    QString* image_path;
    Virtaus::Core::Attribute* parent;
};

class Virtaus::Core::Product : public QObject
{
public:
    Product(const Virtaus::Core::Category *parent);

    QString* getName();
    QMap<QString, Virtaus::Core::Item*>* getItemList();
    const Virtaus::Core::Category* getParent();

    void setName (const QString& name);

private:
    QString *name;
    QMap<QString, Virtaus::Core::Item*> *items;
    const Virtaus::Core::Category* parent;
};

class Virtaus::Core::Set : public QObject
{
public:
    explicit Set (Virtaus::Core::Collection *parent);

    QString* getName();
    QMap<QString, Virtaus::Core::Product*>* getProductList();
    Virtaus::Core::Collection* getParent();

    void setName (const QString& name);

protected:
    QString* name;
    QMap<QString, Virtaus::Core::Product*>* products;
    Virtaus::Core::Collection* parent;
};

#endif // COLLECTION_H
