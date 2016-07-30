#include "imagelabellingscene.h"

#include <string>
#include <QGraphicsPathItem>

ImageLabellingScene::ImageLabellingScene() :
    labellingState(0)
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
        gMouseoverItems["horizontalLine"] = new QGraphicsLineItem(QLineF(point, point+QPointF(1,0)));
        // Make a vertical line going through point
        gMouseoverItems["verticalLine"] = new QGraphicsLineItem(QLineF(point, point+QPointF(0,1)));
    } else if (labellingState >= 2 && labellingState <= 5){
        // We have a small circle following the cursor instead now
        gMouseoverItems["circle"] = new QGraphicsEllipseItem(point.x(), point.y(), .1, .1, this);
    }
}

void ImageLabellingScene::mouseMoveOnImage(QPointF point)
{
    if(labellingState <= 1 && gMouseoverItems.contains("horizontalLine")
            && gMouseoverItems.contains("verticalLine")) {
        gMouseoverItems["horizontalLine"]->setLine(QLineF(point, point+QPointF(1,0)));
        gMouseoverItems["verticalLine"]->setLine(QLineF(point, point+QPointF(0,1)));
    } else if (labellingState >= 2 && labellingState <= 5
               && gMouseoverItems.contains("circle")){
        // Update position of the dot following the cursor
        gMouseoverItems["circle"]->setRect(point.x(), point.y(), .1, .1);
    }

}

void ImageLabellingScene::mouseLeaveImage()
{
    QMap<QString, *QGraphicsItem>::const_iterator i = gMouseoverItems.constBegin();
    while (i != gMouseoverItems.constEnd()) delete i.value();
}

void ImageLabellingScene::mouseClickImage(QPointF point)
{
    QMap<QString, *QGraphicsItem>::const_iterator i = gMouseoverItems.constBegin();
    while (i != gMouseoverItems.constEnd()) delete i.value(); // the mouseOver items should vanish now.

    switch(labellingState){
    case 0:
        gTempItems["horizontalLine"] = new QGraphicsLineItem(QLineF(point, point+QPointF(0,1)));
        gTempItems["verticalLine"] = new QGraphicsLineItem(QLineF(point, point+QPointF(1,0)));
        break;
    case 1:
        QPointF A = gTempItems["horizontalLine"]->line()->p1();
        QGraphicsRectItem item = new QGraphicsRectItem(QRectF(A, point), this);
        QPen pen = new QPen();
        pen.setStyle(Qt::SolidLine);
        pen.setColor(Qt::magenta);
        item.setPen(pen);

        gPermItems.append(item);

        delete gTempItems.value("horizontalLine");
        delete gTempItems.value("verticalLine");
        gTempItems.remove("horizontalLine");
        gTempItems.remove("verticalLine");
        break;
    case 2:
        gTempItems["transformedRect"] = new QGraphicsPathItem(this);
        QPainterPath path = QPainterPath(point);
        gTempItems.value("transformedRect")->setPath(path);
        break;
    case 3:
    case 4:
        QPainterPath path = gTempItems["transformedRect"]->path();
        path.lineTo(point);
        gTempItems["transformedRect"]->setPath(path);
        break;
    case 5:
        QPainterPath path = gTempItems["transformedRect"]->path();
        path.lineTo(point);
        path.closeSubpath();
        QPolygonF quad = path.toFillPolygon();
        QGraphicsPolygonItem poly = new QGraphicsPolygonItem(quad);
        gPermItems.append(poly);
        break;
    case 6:
        // we shouldn't be doing anything here with clicks.  Depend on next to go to next.
        break;
    }

}

void ImageLabellingScene::forward()
{
    if (labellingState <= 5){
        labellingState++;
    } else if ( labellingState == 6) {
        // we want to save the current state
    }

}

void ImageLabellingScene::back()
{
    // Left unimplemented for now
}
