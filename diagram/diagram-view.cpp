#include "diagram-view.h"
#include <iostream>

DiagramView::DiagramView(QWidget *parent) :
    QWidget(parent)
{
    this->current = NULL;

    this->setLayout(new QVBoxLayout(this));
    this->layout()->setSpacing(0);
    this->layout()->setMargin(0);
    this->layout()->setContentsMargins(0, 0, 0, 0);
}

void
DiagramView::setCategory (Virtaus::Core::Category* category) {
    if (!category) return;

    this->current = category;

    // Remove previous items
    QLayoutItem *item;
    while((item = this->layout()->takeAt(0))) {
        delete item->widget();
        delete item;
    }

    Virtaus::Core::DataReader* reader = new Virtaus::Core::DataReader;

    // TODO: reimplement Virtaus::Category loading
    /*
    foreach (QString path, *category->getAttributeList()) {
        //std::cout << "Loading path: " << collection->getInfo("path").toStdString() << "/" << path.toStdString() << "\n";

        if (!reader->isValidCategory(collection->getInfo("path") + "/" + path))
            continue;

        Virtaus::Category* category = reader->loadCategory(collection->getInfo("path") + "/" + path);
        category->setParent(collection);
        category->setName(path);

        DiagramRow* row = new DiagramRow(this);
        row->setAttribute(category);

        this->layout()->addWidget(row);
        this->layout()->setAlignment(row, Qt::AlignTop);
    }

    this->layout()->addItem(new QSpacerItem(0, 10, QSizePolicy::Expanding, QSizePolicy::Expanding));
    */

    delete reader;
}
