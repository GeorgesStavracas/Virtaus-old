#include "cover-art-widget.h"
#include "ui_cover-art-widget.h"

CoverArtWidget::CoverArtWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CoverArtWidget)
{
    ui->setupUi(this);
}

CoverArtWidget::~CoverArtWidget()
{
    delete ui;
}
