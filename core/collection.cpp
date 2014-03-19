#include "collection.h"

using namespace Virtaus;



/*
 * Attribute class
 */
Attribute::Attribute(Virtaus::Category* parent) : QObject(parent) {
    this->itemlist = new QMap<QString, Virtaus::Item*>;
    this->name = new QString("");
    this->z_index = 0;
}

Attribute::~Attribute() {
    foreach (Item* i, this->itemlist->values())
        delete i;

    delete this->itemlist;
    delete this->name;

}

QMap<QString, Virtaus::Item*>*
Attribute::getItemList() {
    return this->itemlist;
}

QString*
Attribute::getName() {
    return new QString(*this->name);
}

Virtaus::Category*
Attribute::getParent() {
    return this->parent;
}

QString&
Attribute::getPath() {
    QString *path = new QString(this->parent->getPath());
    path->append("/" + *this->name);
    return *path;
}

int
Attribute::getZIndex() {
    return this->z_index;
}

void
Attribute::setName(QString &name) {
    delete this->name;
    this->name = new QString(name);
}

void
Attribute::setZIndex(int index) {
    this->z_index = index;
}






/*
 * Category class
 */

Category::Category(Virtaus::Collection *parent) {
    this->name = new QString ("");
    this->point = new QPoint(0, 0);
    this->size = new QSize(0, 0);
    this->attribs = new QMap<QString, Virtaus::Attribute*>;
    this->products = new QMap<QString, Virtaus::Product*>;
    this->parent = parent;
}

Category::~Category() {
    delete this->name;
    delete this->point;
    delete this->size;

    foreach (Attribute* a, this->attribs->values())
        delete a;

    delete this->attribs;

    foreach (Product* p, this->products->values())
        delete p;

    delete this->products;
}

QString*
Category::getName () {
    return new QString (*(this->name));
}

QPoint*
Category::getPoint () {
    return new QPoint (this->point->rx(), this->point->ry());
}

QSize*
Category::getSize () {
    return new QSize (this->size->rwidth(), this->size->rheight());
}

QString&
Category::getPath() {
    QString* path = new QString;
    path->append(this->parent->getInfo("path") + "/");
    path->append(this->getName());
    return *path;
}

Virtaus::Collection*
Category::getParent() {
    return this->parent;
}

QMap<QString, Virtaus::Attribute*>*
Category::getAttributeList() {
    return this->attribs;
}

QMap<QString, Virtaus::Product*>*
Category::getProductList() {
    return this->products;
}

void
Category::setName (const QString name) {
    delete this->name;
    this->name = new QString(name);
}

void
Category::setPoint (QPoint *point){

    this->point->setX(point->rx());
    this->point->setY(point->ry());
}

void
Category::setSize (QSize *size) {
    this->size->setWidth(size->width());
    this->size->setHeight(size->height());
}







/*
 * Collection class
 */

Collection::Collection() : QObject() {
    this->info = new QMap<QString, QString>;
    this->categories = new QMap<QString, Virtaus::Category*>;
    this->sets = new QMap<QString, Virtaus::Set*>;
}

Collection::~Collection() {
    delete this->info;

    foreach (Category* c, this->categories->values())
        delete c;

    delete this->categories;

    foreach (Set* s, this->sets->values())
        delete s;

    delete this->sets;
}

QString
Collection::getInfo (QString field) {
    if (this->info->isEmpty()) return "";
    if (!this->info->contains(field)) return "";

    return this->info->value(field);
}

QMap<QString, Virtaus::Category*>*
Collection::getCategories() {
    return this->categories;
}

QMap<QString, Virtaus::Set*>*
Collection::getSets() {
    return this->sets;
}

void
Collection::setInfo (QString key, QString value) {
    this->info->insert(key, value);
}





/*
 * Item class
 */
Item::Item(Virtaus::Attribute* parent) {
    this->image = NULL;
    this->image_path = new QString;
    this->name = new QString;
    this->parent = parent;
}

Item::~Item() {
    if (this->image)
        delete this->image;
    delete this->image_path;
    delete this->name;
}

QImage*
Item::getImage() {
    if (!this->image)
        this->image = new QImage(*this->image_path);

    return this->image;
}

QString*
Item::getName() {
    return new QString (*(this->name));
}

QString&
Item::getPath() {
    QString* path = new QString(this->parent->getPath());
    path->append(this->name);
    return *path;
}

void
Item::setImage (const QString &path) {
    this->image_path->clear();
    this->image_path->append(path);
}

void
Item::setName (const QString &name) {
    this->name->clear();
    this->name->append(name);
}







/*
 * Product class
 */
Product::Product (const Category *parent) {
    this->parent = parent;
    this->items = new QMap<QString, Virtaus::Item*>;
    this->name = new QString;
}

QString*
Product::getName() {
    return new QString(*this->name);
}

QMap<QString, Virtaus::Item*>*
Product::getItemList() {
    return this->items;
}

const Virtaus::Category*
Product::getParent() {
    return this->parent;
}

void
Product::setName (const QString &name) {
    this->name->clear();
    this->name->append(name);
}







/*
 * Set class
 */
Set::Set (Virtaus::Collection *parent) {
    this->parent = parent;
    this->products = new QMap<QString, Virtaus::Product*>;
    this->name = new QString;
}

QString*
Set::getName() {
    return new QString(*this->name);
}

QMap<QString, Virtaus::Product*>*
Set::getProductList() {
    return this->products;
}

Virtaus::Collection*
Set::getParent() {
    return this->parent;
}

void
Set::setName (const QString &name) {
    this->name->clear();
    this->name->append(name);
}
