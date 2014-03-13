#include "collection.h"

using namespace Virtaus;



/*
 * Attribute class
 */
Attribute::Attribute() {
    this->itemlist = new QList<Virtaus::Item>;
    this->name = new QString("");
    this->z_index = 0;
}

QList<Virtaus::Item>
Attribute::getItemList() {
    return *this->itemlist;
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
    return *(new QString(*this->name));
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
Attribute::setParent(Category *parent) {
    this->parent = parent;
}

void
Attribute::setZIndex(int index) {
    this->z_index = index;
}






/*
 * Category class
 */

Category::Category() {
    this->name = new QString ("");
    this->point = new QPoint(0, 0);
    this->size = new QSize(0, 0);
    this->attribs = new QList<Virtaus::Attribute>;
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
    QString path = this->parent->getInfo("path") + "/";
    path += *this->getName();
    return path;
}

Virtaus::Collection*
Category::getParent() {
    return this->parent;
}

QList<Virtaus::Attribute>
Category::getAttributeList() {
    return *this->attribs;
}

void
Category::setParent (Virtaus::Collection* parent) {
    this->parent = parent;
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

Collection::Collection() {
    this->info = new QMap<QString, QString>;
    this->categories = new QLinkedList<Virtaus::Category>;
}

QString
Collection::getInfo (QString field) {
    if (this->info->isEmpty()) return "";
    if (!this->info->contains(field)) return "";

    return this->info->value(field);
}

QLinkedList<Virtaus::Category>
Collection::getCategories() {
    return *this->categories;
}

void
Collection::setInfo (QString key, QString value) {
    this->info->insert(key, value);
}





/*
 * Item class
 */
Item::Item(Virtaus::Category* parent) {
    this->image = new QImage();
    this->name = new QString();
    this->parent = parent;
}

QImage*
Item::getImage() {
    return this->image;
}

QString*
Item::getName() {
    return new QString (*(this->name));
}

void
Item::setImage (const QString &path) {
    delete this->image;

    this->image = new QImage (path);
}

void
Item::setName (const QString &name) {
    this->name->clear();
    this->name->append(name);
}







/*
 * Product class
 */
Product::Product (const Collection *parent) {
    this->parent = parent;
    this->items = new QList<Virtaus::Item>;
    this->name = new QString;
}

QString*
Product::getName() {
    return new QString(*this->name);
}

QList<Virtaus::Item>
Product::getItemList() {
    return *this->items;
}

const Virtaus::Collection*
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
Set::Product (const Virtaus::Collection *parent) {
    this->parent = parent;
    this->items = new QList<Virtaus::Item>;
    this->name = new QString;
}

QString*
Set::getName() {
    return new QString(*this->name);
}

QList<Virtaus::Product*>
Set::getItemList() {
    return *this->items;
}

const Virtaus::Collection*
Set::getParent() {
    return this->parent;
}

void
Set::setName (const QString &name) {
    this->name->clear();
    this->name->append(name);
}
