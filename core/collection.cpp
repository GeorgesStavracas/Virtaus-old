#include "collection.h"

using namespace Virtaus;

/*
 * Collection class
 */

Collection::Collection() {
    this->info = new QMap<QString, QString>;
    this->categories = new QLinkedList<QString>;
}

QString
Collection::getInfo (QString field) {
    if (this->info->isEmpty()) return "";
    if (!this->info->contains(field)) return "";

    return this->info->value(field);
}

QLinkedList<QString>*
Collection::getCategories() {
    return this->categories;
}

void
Collection::setInfo (QString key, QString value) {
    this->info->insert(key, value);
}


/*
 * Category class
 */

Category::Category() {
    this->name = new QString ("");
    this->point = new QPoint(0, 0);
    this->size = new QSize(0, 0);
    this->itemlist = new QList<Virtaus::Item>;
}

/*
 * Getters and setters
 */
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

const Virtaus::Collection*
Category::getParent() {
    return this->parent;
}

QList<Virtaus::Item>*
Category::getItemList() {
    return this->itemlist;
}

void
Category::setParent (const Virtaus::Collection* parent) {
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

void
Category::addItem (Item *item) {
    this->itemlist->append(*item);
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

QList<Virtaus::Item>*
Product::getItemList() {
    return this->items;
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
