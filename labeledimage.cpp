#include "labeledimage.h"



LabeledImage::LabeledImage()
{
    QGraphicsPixmapItem::QGraphicsPixmapItem();
    this->setAttribute(Qt::WA_Hover, true);
    setAcceptHoverEvents(true);
}

LabeledImage::~LabeledImage() {
    delete bBoxes;
    QGraphicsPixmapItem::~QGraphicsPixmapItem();
}

virtual void LabeledImage::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    emit mouseEnterImage(event->scenePos());
    QGraphicsPixmapItem::hoverEnterEvent(event);
}

virtual void LabeledImage::hoverMoveEvent(QGraphicsSceneHoverEvent *event){
    emit mouseMoveOnImage(event->scenePos());
    QGraphicsPixmapItem::hoverMoveEvent(event);
}

virtual void LabeledImage::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    emit mouseLeaveImage();
    QGraphicsPixmapItem::hoverLeaveEvent(event);
}

virtual void LabeledImage::mouseReleaseEvent(QGraphicsSceneHoverEvent *event){
    emit mouseClickImage(event->scenePos());
    QGraphicsPixmapItem::mouseReleaseEvent(event);
}
