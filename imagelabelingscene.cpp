#include "imagelabelingscene.h"

#include <string>
#include <QGraphicsPathItem>
#include <QGraphicsEllipseItem>
#include <QMessageBox>

QPainterPath createPath(QPointF points[], int size);

ImageLabelingScene::ImageLabelingScene() :
    QGraphicsScene(),
    labelingState(0),
    tempSavedPoints{QPointF(), QPointF(), QPointF(), QPointF()}
{
    currentBox.x = -1;
    currentBox.y = -1;
    currentBox.h = -1;
    currentBox.w = -1;
}

ImageLabelingScene::ImageLabelingScene(LabeledImage &labeledImage) :
    currentLabeledImage(&labeledImage)
{
    ImageLabelingScene();
    this->addItem(&labeledImage);
}

ImageLabelingScene::~ImageLabelingScene() {
}

void ImageLabelingScene::mouseEnterImage(QPointF point)
{
    switch(labelingState % totalStates){
    case 0:
    case 1: {
        modifyOrNew<QGraphicsLineItem>(gMouseoverItems, "horizontalLine")
            ->setLine(QLineF(point, point+QPointF(1,0)));
        modifyOrNew<QGraphicsLineItem>(gMouseoverItems, "verticalLine")
            ->setLine(QLineF(point, point+QPointF(0,1)));
        break; }
    case 2: {
        modifyOrNew<QGraphicsEllipseItem>(gMouseoverItems, "circle")
            ->setRect(QRectF(point.x()-.05, point.y()-.05,.1, .1));
        break; }
    case 3: {
        modifyOrNew<QGraphicsEllipseItem>(gMouseoverItems, "circle")
            ->setRect(QRectF(point.x()-.05, point.y()-.05,.1, .1));
        QGraphicsPathItem *path = modifyOrNew<QGraphicsPathItem>(gMouseoverItems, "path");
        path->setPath(createPath(tempSavedPoints, 2));
        path->setPen(QPen(Qt::DashLine));

        break; }
    case 4: {
        modifyOrNew<QGraphicsEllipseItem>(gMouseoverItems, "circle")
            ->setRect(QRectF(point.x()-.05, point.y()-.05,.1, .1));
        QGraphicsPathItem *path = modifyOrNew<QGraphicsPathItem>(gMouseoverItems, "path");
        path->setPath(createPath(tempSavedPoints, 3));
        path->setPen(QPen(Qt::DashLine));
        break; }
    case 5: {
        modifyOrNew<QGraphicsEllipseItem>(gMouseoverItems, "circle")
            ->setRect(QRectF(point.x()-.05, point.y()-.05,.1, .1));
        QGraphicsPathItem *path = modifyOrNew<QGraphicsPathItem>(gMouseoverItems, "path");
        path->setPath(createPath(tempSavedPoints, 4));
        path->setPen(QPen(Qt::DashLine));
        path->path().closeSubpath();
        break; }
    }
}

void ImageLabelingScene::mouseMoveOnImage(QPointF point)
{
    ImageLabelingScene::mouseEnterImage(point);
}

void ImageLabelingScene::mouseLeaveImage()
{
    for(QString i: gMouseoverItems.keys()) deleteItem(gMouseoverItems, i);
}

void ImageLabelingScene::mouseClickImage(QPointF point)
{
    switch(labelingState % totalStates) {
    case 0: {
        gTempItems["horizontalLine"] = modifyOrNew<QGraphicsLineItem>(gMouseoverItems, "horizontalLine");
        gTempItems["verticalLine"] = modifyOrNew<QGraphicsLineItem> (gMouseoverItems, "verticalLine");
        // Must ensure that these items are not modified later by future calls to modifyOrNew(gMouseoverItems,"")
        gMouseoverItems.remove("horizontalLine");
        gMouseoverItems.remove("verticalLine");
        emit newInstruction("Select bottom-right side of the bounding rectangle","");
        labelingState++;
        break; }
    case 1: {
        QPointF point1 = dynamic_cast<QGraphicsLineItem*>(gTempItems["horizontalLine"])->line().p1();
        QRectF rect(point1, point);
        QGraphicsRectItem *item = new QGraphicsRectItem(rect);
        QPen pen = QPen();
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
        emit newInstruction("Select top-left corner of bounding quadrilateral inside current bounding rectangle.",
                            QString("Rectangle %1 labeled ").arg(labelingState/totalStates + 1));
        labelingState++;
        break; }
    case 2: {
        QGraphicsEllipseItem *circle1 = modifyOrNew<QGraphicsEllipseItem>(gTempItems, "circle1");
        circle1->setRect(QRectF(point.x()-.05, point.y()-.05,.1, .1));
        tempSavedPoints[0] = point;
        emit newInstruction("Select top-right corner of bounding quadrilateral inside current bounding rectangle \
                                (proceed clockwise)","");
        labelingState++;
        break; }
    case 3: {
        tempSavedPoints[1] = point;
        QGraphicsEllipseItem *circle2 = modifyOrNew<QGraphicsEllipseItem>(gTempItems, "circle2");
        circle2->setRect(QRectF(point.x()-.05, point.y()-.05,.1, .1));

        QGraphicsPathItem *path = modifyOrNew<QGraphicsPathItem>(gTempItems, "path");
        path->setPath(createPath(tempSavedPoints, 2));
        path->setPen(QPen(Qt::SolidLine));
        emit newInstruction("Select next corner of bounding quadrilateral inside current bounding rectangle \
                                (proceed clockwise)","");
        labelingState++;
        break; }
    case 4: {
        tempSavedPoints[2] = point;
        QGraphicsEllipseItem *circle3 = modifyOrNew<QGraphicsEllipseItem>(gTempItems, "circle3");
        circle3->setRect(QRectF(point.x()-.05, point.y()-.05,.1, .1));

        QGraphicsPathItem *path = modifyOrNew<QGraphicsPathItem>(gTempItems, "path");
        path->setPath(createPath(tempSavedPoints, 3));
        path->setPen(QPen(Qt::SolidLine));
        emit newInstruction("Select last corner of bounding quadrilateral inside current bounding rectangle \
                                (proceed clockwise)", "");
        labelingState++;
        break; }
    case 5: {
        tempSavedPoints[3] = point;
        QGraphicsEllipseItem *circle4 = modifyOrNew<QGraphicsEllipseItem>(gTempItems, "circle4");
        circle4->setRect(QRectF(point.x()-.05, point.y()-.05,.1, .1));

        QGraphicsPathItem *path = modifyOrNew<QGraphicsPathItem>(gTempItems, "path");
        path->setPath(createPath(tempSavedPoints, 4));
        path->path().closeSubpath();

        // Save must be clicked at this point to save current polygon
        emit newInstruction("Press save in order to save the current bounding quadrilateral; \
                                You can instead click on the screen to re-set the last point", "");
        break; }
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
        if (!tempSavedPoints[0].isNull()){
            mouseClickImage(tempSavedPoints[0]);
        }
        break;
    case 3:
        if (!tempSavedPoints[1].isNull()){
            mouseClickImage(tempSavedPoints[1]);
        }
        break;
    case 4:
        if (!tempSavedPoints[2].isNull()){
            mouseClickImage(tempSavedPoints[2]);
        }
        break;
    case 5:
        if (!tempSavedPoints[3].isNull()){
            mouseClickImage(tempSavedPoints[3]);
        }
        break;
    }
}

void ImageLabelingScene::save()
{
    if (labelingState % totalStates) {
        saveCurrent();

        QGraphicsPathItem *path = dynamic_cast<QGraphicsPathItem*>(gTempItems["path"]);
        QGraphicsPolygonItem *poly = new QGraphicsPolygonItem(path->path().toFillPolygon());
        gPermItems.append(poly);
        this->addItem(poly);

        deleteItem(gTempItems, "path");
        for(auto item : gMouseoverItems.keys()) deleteItem(gMouseoverItems, item);
        for(auto item : gTempItems.keys()) deleteItem(gTempItems, item);
        tempSavedPoints[0] = QPointF();
        tempSavedPoints[1] = QPointF();
        tempSavedPoints[2] = QPointF();
        tempSavedPoints[3] = QPointF();

        currentBox.x = -1;
        currentBox.y = -1;
        currentBox.h = -1;
        currentBox.w = -1;

        emit newInstruction("Select top-left side of the bounding rectangle around an object in the image",
                            QString("Labeled object number %1").arg(labelingState/totalStates + 1));
        labelingState ++;

    }
}

void ImageLabelingScene::back()
{
    switch (labelingState % totalStates)
    {
    case 0:
        // Going back here shouldn't do anything unless it's the one that goes from image to image
        break;
    case 1:
        deleteItem(gTempItems, "horizontalLine");
        deleteItem(gTempItems, "verticalLine");

        labelingState--;
        emit newInstruction("Select top-left side of the bounding rectangle around an object in the image","",true);
        break;
    case 2: {
        QGraphicsRectItem *item = dynamic_cast<QGraphicsRectItem*>(gPermItems.last());
        QPointF point = item->rect().topLeft(); // Deletes the last element of gPermItems

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
        emit newInstruction("Select bottom-right side of the bounding rectangle","",true);
        break; }
    case 3:
        deleteItem(gTempItems, "circle1");
        tempSavedPoints[0] = QPointF();
        labelingState--;
        emit newInstruction("Select top-left corner of bounding quadrilateral inside current bounding rectangle.","",true);
        break;
    case 4:
        deleteItem(gTempItems, "circle2");
        deleteItem(gTempItems, "path");
        tempSavedPoints[1] = QPointF();
        labelingState--;
        emit newInstruction("Select top-right corner of bounding quadrilateral inside current bounding rectangle \
                                (proceed clockwise)","", true);
        break;
    case 5: {
        if (tempSavedPoints[3].isNull()) {
            // case 5: in mouseClickImage has not yet run
            deleteItem(gTempItems, "circle3");
            deleteItem(gTempItems, "path");
            QGraphicsPathItem *path = modifyOrNew<QGraphicsPathItem>(gTempItems, "path");
            path->setPath(createPath(tempSavedPoints, 2));
            path->setPen(Qt::SolidLine);
            labelingState--;
            emit newInstruction("Select last corner of bounding quadrilateral inside current bounding rectangle \
                                    (proceed clockwise)", "", true);
        } else { // tempSavedPoints[3].isNull()==false
            tempSavedPoints[3] = QPointF();
            deleteItem(gTempItems, "circle4");

            QGraphicsPathItem *path = modifyOrNew<QGraphicsPathItem>(gTempItems, "path");
            path->setPath(createPath(tempSavedPoints, 3));

            // we don't decrement labelingState, we just return everything to pre-case5: in mouseClickImage state
        }
        break; }
    }
}

void ImageLabelingScene::saveCurrent(){
    if (labelingState % totalStates == 5) {
        auto pair = std::pair<bRect, bRectTransform>(
                    currentBox,
                    currentLabeledImage->findRectTransform(
                        currentBox,
                        tempSavedPoints[0].toPoint(),
                        tempSavedPoints[1].toPoint(),
                        tempSavedPoints[2].toPoint(),
                        tempSavedPoints[3].toPoint()
                        )
                    );
        currentLabeledImage->bBoxes->operator[](labelingState/totalStates) = pair;
    }
}

void ImageLabelingScene::changeImage(LabeledImage &labeledImage)
{
    QMessageBox msgBox;
    msgBox.setText("Are you certain you want to load a new image?  Have all bounding boxes been labeled?  Any unsaved work will be lost.");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Yes: {
        for(auto item : gMouseoverItems.keys()) deleteItem(gMouseoverItems, item);
        for(auto item : gTempItems.keys()) deleteItem(gTempItems, item);

        for(auto item : gPermItems)
            this->removeItem(item);
        gPermItems.clear();

        tempSavedPoints[0] = QPointF();
        tempSavedPoints[1] = QPointF();
        tempSavedPoints[2] = QPointF();
        tempSavedPoints[3] = QPointF();

        currentBox.x = -1;
        currentBox.y = -1;
        currentBox.h = -1;
        currentBox.w = -1;

        labelingState = 0;
        currentLabeledImage = &labeledImage;
        break; }
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
        return dynamic_cast<T*>(item.value());
    } else {
        T* retItem = new T();
        map[itemStr] = retItem;
        this->addItem(retItem);
        return retItem ;
    }
}

void ImageLabelingScene::deleteItem(QMap<QString, QGraphicsItem*> &map, QString itemStr){
    QGraphicsItem *item = map[itemStr];
    if (this->items().contains(item))
        this->removeItem(item);
    if (map.contains(itemStr))
        map.remove(itemStr);
}

QPainterPath createPath(QPointF points[], int size){
    QPainterPath path = QPainterPath(points[0]);
    for (int i=1; i<size; i++){
        path.lineTo(points[i]);
    }
    return path;
}
