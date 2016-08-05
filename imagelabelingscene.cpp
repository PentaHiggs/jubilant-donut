#include "imagelabelingscene.h"

#include <string>
#include <QGraphicsPathItem>
#include <QGraphicsEllipseItem>
#include <QMessageBox>

QPainterPath createPath(QPoint points[], int size);

ImageLabelingScene::ImageLabelingScene() :
    labelingState(0),
    tempSavePoints{QPointF(), QPointF(), QPointF(), QPointF()}
{
    QGraphicsScene::QGraphicsScene();
    currentBox.x = -1;
    currentBox.y = -1;
    currentBox.h = -1;
    currentBox.w = -1;
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
        this->addItem(item);

        deleteItem(gTempItems, "horizontalLine");
        deleteItem(gTempItems, "verticalLine");

        int x; int y; int w; int h;
        rect.toRect().getRect(&x, &y, &w, &h);
        currentBox.x = x;
        currentBox.y = y;
        currentBox.h = h;
        currentBox.w = w;

        labelingState++;
        break;
    case 2:
        QGraphicsEllipseItem circle1 = modifyOrNew<QGraphicsEllipseItem>(gTempItems, "circle1");
        circle1->setRect(QRectF(QPointF(point.x()-.05, point.y()-.05),.1, .1));
        tempSavePoints[0] = point;
        labelingState++;
        break;
    case 3:
        tempSavePoints[1] = point;
        QGraphicsEllipseItem circle2 = modifyOrNew<QGraphicsEllipseItem>(gTempItems, "circle2");
        circle2->setRect(QRectF(QPointF(point.x()-.05, point.y()-.05),.1, .1));

        QGraphicsPathItem *path = modifyOrNew<QGraphicsPathItem>(gTempItems, "path");
        path->setPath(createPath(tempSavedPoints, 2));
        path->setPen(QPen(Qt::SolidLine));
        labelingState++;
        break;
    case 4:
        tempSavePoints[2] = point;
        QGraphicsEllipseItem circle3 = modifyOrNew<QGraphicsEllipseItem>(gTempItems, "circle3");
        circle3->setRect(QRectF(QPointF(point.x()-.05, point.y()-.05),.1, .1));

        QGraphicsPathItem *path = modifyOrNew<QGraphicsPathItem>(gTempItems, "path");
        path->setPath(createPath(tempSavedPoints, 3));
        path->setPen(QPen(Qt::SolidLine));
        labelingState++;
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
        this->addItem(poly);

        deleteItem(gTempItems, "path");
        // Save must be clicked at this point to save current polygon
        break;
    }
}

void ImageLabelingScene::forward()
{
    switch(labelingState % totalStates)
    {
    case 0:
        break;
    case 1:
        break;
    case 2:
        if (!tempSavePoints[0].isNull()){
            mouseClickImage(tempSavePoints[0]);
            labelingState++;
        }
        break;
    case 3:
        if (!tempSavePoints[1].isNull()){
            mouseClickImage(tempSavePoints[1]);
            labelingState++;
        }
        break;
    case 4:
        if (!tempSavePoints[2].isNull()){
            mouseClickImage(tempSavePoints[2]);
        }
        break;
    case 5:
        if (!tempSavePoints[3].isNull()){
            mouseClickImage(tempSavePoints[2]);
        }
        break;
    }
}

void ImageLabelingScene::save()
{
    if (labelingState % totalStates) {
        saveCurrent();

        for(auto item : gMouseoverItems) deleteItem(gMouseoverItems, item);
        for(auto item : gTempItems) deleteItem(gTempItems, item);
        tempSavePoints[0] = QPointF();
        tempSavePoints[1] = QPointF();
        tempSavePoints[2] = QPointF();
        tempSavePoints[3] = QPointF();

        currentBox.x = -1;
        currentBox.y = -1;
        currentBox.h = -1;
        currentBox.w = -1;
        labelingState ++;
    }
}

void ImageLabelingScene::back()
{
    case 0:
        // Going back here shouldn't do anything unless it's the one that goes from image to image
        break;
    case 1:
        deleteItem(gTempItems, "horizontalLine");
        deleteItem(gTempItems, "verticalLine");
        labelingState--;
        break;
    case 2:
        QGraphicsRectItem item = dynamic_cast<QGraphicsRectItem>(gPermItems.last());
        QPointF point = item.rect().topLeft(); // Deletes the last element of gPermItems

        currentBox.x = -1;
        currentBox.y = -1;
        currentBox.h = -1;
        currentBox.w = -1;

        modifyOrNew<QGraphicsLineItem>(gTempItems, "horizontalLine")->
                setLine(QLineF(point, point+QPointF(1,0)));
        modifyOrNew<QGraphicsLineItem>(gTempItems, "verticalLine")->
                setLine(QLineF(point, point+QPointF(0,1)));

        this->removeItem(item);
        gPermItems.erase(gPermItems.end() - 1);
        labelingState--;
        break;
    case 3:
        deleteItem(gTempItems, "circle1");
        tempSavePoints[0] = QPointF();
        labelingState--;
        break;
    case 4:
        deleteItem(gTempItems, "circle2");
        deleteItem(gTempItems, "path");
        tempSavePoints[1] = QPointF();
        labelingState--;
    case 5:
        if (tempSavePoints[3].isNull()) {
            // case 5: in mouseClickImage has not yet run
            tempSavePoints[3] = QPointF();
            deleteItem(gTempItems, "circle3");
            deleteItem(gTempItems, "path");
            QGraphicsPathItem *path = modifyOrNew<QGraphicsPathItem>(gTempItems, "path");
            path->setPath(createPath(tempSavedPoints, 2));
            path->setPen(Qt::SolidLine);
            labelingState--;
        } else { // tempSavePoints[3].isNull()==false
            tempSavePoints[4] = QPointF();
            deleteItem(gTempItems, "circle4");
            QGraphicsItem *item = gPermItems.last();
            this->removeItem(item);
            gPermItems.erase(gPermItems.end() - 1);

            QGraphicsPathItem *path = modifyOrNew<QGraphicsPathItem>(gTempItems, "path");
            path->setPath(createPath(tempSavedPoints, 3));

            // we don't decrement labelingState, we just return everything to pre-case5: in mouseClickImage state
        }
        break;
}

void ImageLabelingScene::saveCurrent(){
    if (labelingState % totalStates == 5) {
        auto pair = std::pair<bRect, bRectTransform>(
                    currentBox,
                    currentLabeledImage.findRectTransform(
                        currentBox,
                        tempSavePoints[0],
                        tempSavePoints[1],
                        tempSavePoints[2],
                        tempSavePoints[3]
                        )
                    );
        currentLabeledImage.bBoxes->operator[](labelingState/totalStates) = pair;
    }
}

void ImageLabelingScene::changeImage(LabeledImage &labeledImage)
{
    QMessageBox msgBox;
    msgBox.setText("Are you certain you want to load a new image?  Have all bounding boxes been labeled?  Any unsaved work will be lost.");
    msg.setStandardbuttons(QMessageBox::Yes || QMessageBox::No);
    msg.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Yes:
        for(auto item : gMouseoverItems) deleteItem(gMouseoverItems, item);
        for(auto item : gTempItems) deleteItem(gTempItems, item);

        for(auto item : gPermItems) this->removeItem(item);
        gPermItems.removeAll();

        tempSavePoints[0] = QPointF();
        tempSavePoints[1] = QPointF();
        tempSavePoints[2] = QPointF();
        tempSavePoints[3] = QPointF();

        currentBox.x = -1;
        currentBox.y = -1;
        currentBox.h = -1;
        currentBox.w = -1;

        labelingState = 0;
        currentLabeledImage = labeledImage;
        break;
    case QMessageBox::No:
        return;
    default:
        return;
    }

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
