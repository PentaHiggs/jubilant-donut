#include "imagelabelingscene.h"

#include <string>
#include <QGraphicsPathItem>
#include <QGraphicsEllipseItem>


QPainterPath createPath(QPoint points[], int size);

ImageLabelingScene::ImageLabelingScene() :
    labelingState(0),
    tempSavePoints{QPointF(), QPointF(), QPointF(), QPointF()}
{
    QGraphicsScene::QGraphicsScene();
}

ImageLabelingScene::ImageLabelingScene(LabeledImage labeledImage) :
    currentLabeledImage(labeledImage)
{
    ImageLabelingScene();
    this->addItem(labeledImage);
}

ImageLabelingScene::~ImageLabelingScene() {
    QGraphicsScene::~QGraphicsScene();
}

void ImageLabelingScene::mouseEnterImage(QPointF point)
{
    switch(labelingState % totalStates){
    case 0:
    case 1:
        modifyOrNew<QGraphicsLineItem>(gMouseoverItems, "horizontalLine")
            ->setLine(QLineF(point, point+QPointF(1,0)));
        modifyOrNew<QGraphicsLineItem>(gMouseOverItems, "verticalLine")
            ->setLine(QLineF(point, point+QPointF(0,1)));
        break;
    case 2:
        modifyOrNew<QGraphicsEllipseItem>(QMouseoverItems, "circle")
            ->setRect(QRectF(QPointF(point.x()-.05, point.y()-.05),.1, .1));
        break;
    case 3:
        modifyOrNew<QGraphicsEllipseItem>(gMouseoverItems, "circle")
            ->setRect(QRectF(QPointF(point.x()-.05, point.y()-.05),.1, .1));
        QGraphicsPathItem *path = modifyOrNew<QGraphicsPathItem>(QMouseOverItems, "path");
        path->setPath(createPath(tempSavedPoints, 2));
        path->setPen(QPen(Qt::DashLine));

        break;
    case 4:
        modifyOrNew<QGraphicsEllipseItem>(gMouseoverItems, "circle")
            ->setRect(QRectF(QPointF(point.x()-.05, point.y()-.05),.1, .1));
        QGraphicsPathItem *path = modifyOrNew<QGraphicsPathItem>(QMouseOverItems, "path");
        path->setPath(createPath(tempSavedPoints, 3));
        path->setPen(QPen(Qt::DashLine));
        break;
    case 5:
        modifyOrNew<QGraphicsEllipseItem>(gMouseoverItems, "circle")
            ->setRect(QRectF(QPointF(point.x()-.05, point.y()-.05),.1, .1));
        QGraphicsPathItem *path = modifyOrNew<QGraphicsPathItem>(QMouseOverItems, "path");
        path->setPath(createPath(tempSavedPoints, 4));
        path->setPen(QPen(Qt::DashLine));
        path->closeSubpath();
        break;
    }
}

void ImageLabelingScene::mouseMoveOnImage(QPointF point)
{
    ImageLabelingScene::mouseEnterImage(point);
}

void ImageLabelingScene::mouseLeaveImage()
{
    for(QGraphicsItem i: gMouseoverItems) deleteItem(gMouseoverItems, i);
}

void ImageLabelingScene::mouseClickImage(QPointF point)
{
    switch(labelingState % totalStates) {
    case 0:
        gTempItems["horizontalLine"] = modifyOrNew<QGraphicsLineItem>(gMouseoverItems, "horizontalLine");
        gTempItems["verticalLine"] = modifyOrNew<QGraphicsLineItem> (gMouseoverItems, "verticalLine");
        // Must ensure that these items are not modified later by future calls to modifyOrNew(gMouseoverItems,"")
        gMouseoverItems.remove("horizontalLine");
        gMouseoverItems.remove("verticalLine");
        labelingState++;
        break;
    case 1:
        QPointF point1 = dynamic_cast<QGraphicsLineItem*>(gTempItems["horizontalLine"])->line().p1();
        QRectF rect(point1, point);
        QGraphicsRectItem *item = new QGraphicsRectItem(rect, this);
        QPen pen = new QPen();
        pen.setColor(Qt::magenta);
        item->setPen(pen);
        gPermItems.append(item);

        deleteItem(gTempItems, "horizontalLine");
        deleteItem(gTempItems, "verticalLine");

        int x; int y; int w; int h;
        rect.toRect().getRect(&x, &y, &w, &h);
        currentBox.x = x;
        currentBox.y = y;
        currentBox.h = h;
        currentBox.w = w;

        // labellingState++;
        break;
    case 2:
        QGraphicsEllipseItem circle1 = modifyOrNew<QGraphicsEllipseItem>(gTempItems, "circle1");
        circle1->setRect(QRectF(QPointF(point.x()-.05, point.y()-.05),.1, .1));
        tempSavePoints[0] = point;
        break;
    case 3:
        tempSavePoints[1] = point;
        QGraphicsEllipseItem circle2 = modifyOrNew<QGraphicsEllipseItem>(gTempItems, "circle2");
        circle2->setRect(QRectF(QPointF(point.x()-.05, point.y()-.05),.1, .1));

        QGraphicsPathItem *path = modifyOrNew<QGraphicsPathItem>(gTempItems, "path");
        path->setPath(createPath(tempSavedPoints, 2));
        path->setPen(QPen(Qt::SolidLine));
        break;
    case 4:
        tempSavePoints[2] = point;
        QGraphicsEllipseItem circle3 = modifyOrNew<QGraphicsEllipseItem>(gTempItems, "circle3");
        circle3->setRect(QRectF(QPointF(point.x()-.05, point.y()-.05),.1, .1));

        QGraphicsPathItem *path = modifyOrNew<QGraphicsPathItem>(gTempItems, "path");
        path->setPath(createPath(tempSavedPoints, 3));
        path->setPen(QPen(Qt::SolidLine));
        break;
    case 5:
        tempSavePoints[3] = point;
        QGraphicsEllipseItem circle4 = modifyOrNew<QGraphicsEllipseItem>(gTempItems, "circle4");
        circle4->setRect(QRectF(QPointF(point.x()-.05, point.y()-.05),.1, .1));

        QGraphicsPathItem *path = modifyOrNew<QGraphicsPathItem>(gTempItems, "path");
        path->setPath(createPath(tempSavedPoints, 4));
        path->closeSubpath();

        QGraphicsPolygonItem *poly = new QGraphicsPolygonItem(path->toFillPolygon());
        gPermItems.append(poly);

        deleteItem(gTempItems, "path");
        break;
    }
}

void ImageLabelingScene::forward()
{
    switch(labellingState % totalStates)
    {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        break;
    }

}

void ImageLabelingScene::back()
{
    // Left unimplemented for now
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        break;
}

template<typename T>
T* ImageLabelingScene::modifyOrNew(QMap<QString, QGraphicsItem*> &map, QString itemStr){
    auto item = map.find(itemStr);
    if (item != map.end()){
        return dynamic_cast<T*>(item);
    } else {
        item = new T();
        map[itemStr] = item;
        this->addItem(item);
        return item;
    }
}

void ImageLabelingScene::deleteItem(QMap<QString, QGraphicsItem*> &map, QString itemStr){
    QGraphicsItem *item = map[itemStr];
    if (this->items().contains(item))
        this->removeItem(item);
    if (map.contains(itemStr))
        map.remove(itemStr);
}

QPainterPath createPath(QPoint points[], int size){
    QPainterPath path = QPainterPath(points[0]);
    for (int i=1; i<size; i++){
        path.lineTo(points[i]);
    }
    return path;
}