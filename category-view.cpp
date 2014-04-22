#include "category-view.h"
#include "ui_category-view.h"

CategoryView::CategoryView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CategoryView)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    VirtausApplication* app = VirtausApplication::getInstance();

    QObject::connect(app, SIGNAL(collectionChanged(Virtaus::Core::Collection*)),
                     this, SLOT(collection_selected(Virtaus::Core::Collection*)));
}

CategoryView::~CategoryView()
{
    delete ui;
}

void
CategoryView::sets_view()
{
    VirtausApplication* app = VirtausApplication::getInstance();

    app->setView(Virtaus::View::COLLECTION_OPTIONS_VIEW);
}

void
CategoryView::resizeEvent(QResizeEvent* event)
{
    scene->setSceneRect(0, 0, ui->graphicsView->size().width(), ui->graphicsView->size().height());
    //qDebug() << ui->graphicsView->sceneRect();
}

void
CategoryView::collection_selected(Virtaus::Core::Collection* c)
{
    if (c)
        paintCategories();
}

void
CategoryView::paintCategories()
{
    VirtausApplication* app = VirtausApplication::getInstance();

    QList<Virtaus::Core::Category*> list;
    list = app->collection()->getCategories()->values();

    QColor color(255,255,255,255);

    foreach (Virtaus::Core::Category* cat, list)
    {
        CategoryRectItem* item = new CategoryRectItem;
        item->setBaseColor(color);

        qreal xscale = scene->sceneRect().width() / app->collection()->getInfo("width").toInt();
        qreal yscale = scene->sceneRect().height() / app->collection()->getInfo("height").toInt();
        qreal x = cat->getPoint()->x() * xscale;
        qreal y = cat->getPoint()->y() * yscale;
        qreal w = cat->getSize()->width() * xscale;
        qreal h = cat->getSize()->height() * yscale;

        item->setPos(x, y);
        item->setRect(QRectF(0, 0, w, h));

        scene->addItem(item);

        qDebug() << "Added item " << *cat->getName();
        qDebug() << *cat->getPoint() << *cat->getSize();
        qDebug() <<xscale << yscale << x << y << w << h;
    }
}
