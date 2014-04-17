#include "cover-art-scene.h"

CoverArtScene::CoverArtScene()
{
    this->scroll_speed = 1;
    current_item = 0;
}

void
CoverArtScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    CoverArtItem* item = (CoverArtItem*) this->itemAt(event->scenePos(), QTransform());

    if (!item)
        return;

    if (clicked_item != item->index())
        return;

    emit itemSelected(item->index());
}

void
CoverArtScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    CoverArtItem* item = (CoverArtItem*) this->itemAt(event->scenePos(), QTransform());

    if (!item)
        clicked_item = -1;
    else
        clicked_item = item->index();
}

void
CoverArtScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    CoverArtItem* item = (CoverArtItem*) this->itemAt(event->scenePos(), QTransform());

    if (item)
        emit itemEdit(item->index());
}


void
CoverArtScene::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left)
        emit itemSelected(currentItem() - 1);

    if (event->key() == Qt::Key_Right)
        emit itemSelected(currentItem() + 1);

    if (event->key() == Qt::Key_End)
        emit itemSelected(-2);

    if (event->key() == Qt::Key_PageUp)
        emit itemSelected(currentItem() + 5);

    if (event->key() == Qt::Key_PageDown)
        emit itemSelected(currentItem() - 5);

    if (event->key() == Qt::Key_Home)
        emit itemSelected(-3);

    if (event->key() == Qt::Key_Enter)
        emit itemEdit(currentItem());
}

