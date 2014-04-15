#include "sets-view.h"
#include "ui_sets-view.h"

SetsView::SetsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetsView)
{
    ui->setupUi(this);
}

SetsView::~SetsView()
{
    delete ui;
}


void
SetsView::show_info()
{
    emit showInfo();
}

void
SetsView::show_products()
{
    emit showProducts();
}

void
SetsView::show_collections()
{
    emit showCollections();
    for (int i = 0; i < 10000; i++)
        QImage* img = new QImage("C:/Usuários/Georges/Imagens/Ico e yorda.jpg");
}
