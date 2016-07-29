#include "imagelabellingscene.h"

ImageLabellingScene::ImageLabellingScene() :
    labellingState(0),
{
    QGraphicsScene::QGraphicsScene();

}

ImageLabellingScene::ImageLabellingScene(LabeledImage labeledImage) :
    labeledImage(labeledImage)
{

    ImageLabellingScene();
}

ImageLabellingScene::~ImageLabellingScene() {
    QGraphicsScene::~QGraphicsScene();
}

void ImageLabellingScene::mouseEnterImage(QPointF point)
{
    if(labellingState==0 || labellingState==1) {
        // Make a horizontal line going through point
        gTempItems["horizontalLine"] = new QGraphicsLineItem(QLineF(point, point+QPointF(1,0)));
        // Make a vertical line going through point
        gTempItems["verticalLine"] = new QGraphicsLineItem(QLineF(point, point+QPointF(0,1)));
    } else if (labellingState >= 2 && labellingState <= 5){
        // We have a small circle following the cursor instead now
        gTempItems["circle"] = new QGraphicsEllipseItem(point.x(), point.y(), .1, .1, this);
    }
}

void ImageLabellingScene::mouseMoveOnImage(QPointF point)
{
    if(labellingState <= 1 && gTempItems.contains("horizontalLine")
            && gTempItems.contains("verticalLine")) {
        gTempItems["horizontalLine"]->setLine(QLineF(point, point+QPointF(1,0)));
        gTempItems["verticalLine"]->setLine(QLineF(point, point+QPointF(0,1)));
    } else if (labellingState >= 2 && labellingState <= 5
               && gTempItems.contains("circle")){
        // Update position of the dot following the cursor
        gTempItems["circle"]->setRect(point.x(), point.y(), .1, .1);
    }

}

void ImageLabellingScene::mouseLeaveImage()
{
    QMap<QString, *QGraphicsItem>::const_iterator i = gTempItems.constBegin();
    while (i != gTempItems.constEnd()) delete i.value();
}

void ImageLabellingScene::mouseClickImage(QPointF point)
{
    QMap<QString, *QGraphicsItem>::const_iterator i = gTempItems.constBegin();
    while (i != gTempItems.constEnd()) delete i.value();

    if (labellingState == 0) {
        gPermItems["horizontalLine"] = new QGraphicsLineItem(QLineF(point, point+QPointF(0,1)));
        gPermItems["verticalLine"] = new QGraphicsLineItem(QLineF(point, point+QPointF(1,0)));
    } else if (labellingState == 1) {
        /* we draw our rectangle using
        QPointF A = gPermItems["horizontalLine"]->line()->p1();
        // we draw rectangle with corners A and point
        */
        delete gPermItems.value("horizontalLine");
        delete gPermItems.value("verticalLine");
        gPermItems.remove("horizontalLine");
        gPermItems.remove("verticalLine");
    }

}

void ImageLabellingScene::forward()
{

}

void ImageLabellingScene::back()
{
    // Left unimplemented for now
}
