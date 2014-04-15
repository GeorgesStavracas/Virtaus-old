#include "diagram-row.h"
#include "ui_diagram-row.h"
#include <iostream>

DiagramRow::DiagramRow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DiagramRow)
{
    ui->setupUi(this);

    this->current = NULL;
    this->model = new QStandardItemModel;
    this->selectable = false;
}

DiagramRow::~DiagramRow()
{

    std::cout << "\nDeleting items...\n";

    QStandardItem* item;

    while ((item = this->model->takeItem(0)))
        delete item;

    this->model->clear();
    delete this->model;

    delete ui;
}

bool
DiagramRow::isSelectable() {
    return this->selectable;
}

void
DiagramRow::setSelectable(bool selectable) {
    this->selectable = selectable;

    if (selectable)
        ui->itemsView->setSelectionMode(QAbstractItemView::SingleSelection);
    else
        ui->itemsView->setSelectionMode(QAbstractItemView::NoSelection);
}

void
DiagramRow::setAttribute(Virtaus::Core::Attribute* attribute) {
    if (!attribute) return;

    /* Clean any previously shown attribute */
    QStandardItem* item;

    while ((item = this->model->takeItem(0)))
        delete item;

    this->model->clear();
    this->current = attribute;

    ui->categoryLabel->setText(*attribute->getName());

    QString collection_path = attribute->getParent()->getParent()->getInfo("path");
    QString path = collection_path + *attribute->getParent()->getName() + "/" + *attribute->getName();

    //TODO: reimplement Virtaus::Attribute loading
    /*
    foreach (QString i, *attribute->getItemList()) {
        std::cout << "Loading path " << (path + "/" + i).toStdString() << "\n";

        QIcon* icon = new QIcon(path + "/" + i);

        QStandardItem *item = new QStandardItem(*icon, i);
        this->model->appendRow(item);

    }
    */

    if (!this->selectable) {
        QIcon* icon = new QIcon (":/virtaus/images/resources/add.svg");
        item = new QStandardItem(*icon, "");
        this->model->appendRow(item);
    }

    ui->itemsView->setModel(this->model);
}

void
DiagramRow::item_selected(QModelIndex index)  {

}
