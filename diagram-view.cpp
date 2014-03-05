#include "diagram-view.h"
#include "ui_diagram-view.h"

DiagramView::DiagramView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DiagramView)
{
    ui->setupUi(this);
}

DiagramView::~DiagramView()
{
    delete ui;
}
