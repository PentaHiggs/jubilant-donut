#include "labeledimage.h"



LabeledImage::LabeledImage()
{
    QGraphicsPixmapItem::QGraphicsPixmapItem();
    QWidget::setMouseTracking(true);
}

LabeledImage::~LabeledImage() {
    delete bBoxes;
    QGraphicsPixmapItem::~QGraphicsPixmapItem();
}

void LabeledImage::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    // insert function call to draw the crosshairs
    QGraphicsPixmapItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event);
}
