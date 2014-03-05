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

    QStandardItem* item;

    while ((item = this->model->takeItem(0)))
        delete item;

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
DiagramRow::setCategory(Virtaus::Category *category) {
    if (!category) return;

    /* Clean any previously shown category */
    QStandardItem* item;

    while ((item = this->model->takeItem(0)))
        delete item;

    this->model->clear();


    this->current = category;

    ui->categoryLabel->setText(*category->getName());

    QString path = category->getParent()->getInfo("path") + "/" + *category->getName();

    foreach (QString i, *category->getItemList()) {
        std::cout << "Loading path " << (path + "/" + i).toStdString() << "\n";

        QIcon* icon = new QIcon(path + "/" + i);

        QStandardItem *item = new QStandardItem(*icon, i);
        this->model->appendRow(item);

    }

    if (!this->selectable) {
        QIcon* icon = new QIcon (":/virtaus/images/resources/add.svg");
        item = new QStandardItem(*icon, "");
        this->model->appendRow(item);
    }

    ui->itemsView->setModel(this->model);
}
