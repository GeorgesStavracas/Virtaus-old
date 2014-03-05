#include "diagram-row.h"
#include "ui_diagram-row.h"

DiagramRow::DiagramRow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DiagramRow)
{
    ui->setupUi(this);
}

DiagramRow::~DiagramRow()
{
    delete ui;
}
