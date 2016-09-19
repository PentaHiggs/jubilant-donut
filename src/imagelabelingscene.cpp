#include "imagelabelingscene.h"

#include <QGraphicsPathItem>
#include <QGraphicsEllipseItem>
#include <QMessageBox>
#include <QtDebug>

QPainterPath createPath(QPointF points[], int size);

ImageLabelingScene::ImageLabelingScene() :
    QGraphicsScene(),
    labelingState(0),
    tempSavedPoints{QPointF(), QPointF(), QPointF(), QPointF()},
    currentLabeledImage(nullptr)
{
    currentBox.x = -1;
    currentBox.y = -1;
    currentBox.h = -1;
    currentBox.w = -1;

    emit newInstruction("Select top-left side of the bounding rectangle around an object in the image","");
}

ImageLabelingScene::ImageLabelingScene(LabeledImage &labeledImage) :
    currentLabeledImage(&labeledImage)
{
    ImageLabelingScene();
    this->addItem(&labeledImage);
}

ImageLabelingScene::~ImageLabelingScene() {
}

const LabeledImage* ImageLabelingScene::returnCurrentImage() const{
    const LabeledImage* cptr = currentLabeledImage;
    return cptr;
}

void ImageLabelingScene::mouseEnterImage(QPointF point)
{
    qDebug() << "mouseEnterImage @ " << point << " w/ state" << labelingState;
    switch(labelingState % totalStates){
    case 0:
    case 1:
        drawCrosshairs(point, gMouseoverItems);
        break;
    case 2:
        drawCircle(point, gMouseoverItems, "circle");
        break;
    case 3: {
        drawCircle(point, gMouseoverItems, "circle");
        QGraphicsPathItem *path = modifyOrNew<QGraphicsPathItem>(gMouseoverItems, "path");
        path->setPath(createPath(tempSavedPoints, 1));
        path->setPen(QPen(Qt::DashLine));

        break; }
    case 4: {
        drawCircle(point, gMouseoverItems, "circle");
        QGraphicsPathItem *path = modifyOrNew<QGraphicsPathItem>(gMouseoverItems, "path");
        path->setPath(createPath(tempSavedPoints, 2));
        path->setPen(QPen(Qt::DashLine));
        break; }
    case 5: {
        drawCircle(point, gMouseoverItems, "circle");
        QGraphicsPathItem *path = modifyOrNew<QGraphicsPathItem>(gMouseoverItems, "path");
        path->setPen(QPen(Qt::DashLine));
        if (tempSavedPoints[3].isNull()) {
            path->setPath(createPath(tempSavedPoints, 3));
            path->setPen(QPen(Qt::DashLine));
        } else {
            QPainterPath pPath = QPainterPath(createPath(tempSavedPoints, 4));
            pPath.closeSubpath();
            path->setPath(pPath);
            }
        break; }
        }

}

void ImageLabelingScene::mouseMoveOnImage(QPointF point)
{
    ImageLabelingScene::mouseEnterImage(point);
}

void ImageLabelingScene::mouseLeaveImage()
{
    qDebug() << "mouseLeaveImage()";
    for(QString i: gMouseoverItems.keys()) deleteItem(gMouseoverItems, i);
}

void ImageLabelingScene::mouseClickImage(QPointF point)
{
    qDebug() << "mouseClickImage @ " << point << " w/ state" << labelingState;
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
        QPointF point1;
        dynamic_cast<QGraphicsLineItem*>(gTempItems["horizontalLine"])->line().intersect(
                    dynamic_cast<QGraphicsLineItem*>(gTempItems["verticalLine"])->line(),
                    &point1
                    );
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
        drawCircle(point, gTempItems, "circle1");
        tempSavedPoints[0] = point;
        emit newInstruction("Select top-right corner of bounding quadrilateral inside current bounding rectangle \
                                (proceed clockwise)","");
        labelingState++;
        break; }
    case 3: {
        tempSavedPoints[1] = point;
        drawCircle(point, gTempItems, "circle2");;

        QGraphicsPathItem *path = modifyOrNew<QGraphicsPathItem>(gTempItems, "path");
        path->setPath(createPath(tempSavedPoints, 2));
        path->setPen(QPen(Qt::SolidLine));
        emit newInstruction("Select next corner of bounding quadrilateral inside current bounding rectangle \
                                (proceed clockwise)","");
        labelingState++;
        break; }
    case 4: {
        tempSavedPoints[2] = point;
        drawCircle(point, gTempItems, "circle3");

        QGraphicsPathItem *path = modifyOrNew<QGraphicsPathItem>(gTempItems, "path");
        path->setPath(createPath(tempSavedPoints, 3));
        path->setPen(QPen(Qt::SolidLine));
        emit newInstruction("Select last corner of bounding quadrilateral inside current bounding rectangle \
                                (proceed clockwise)", "");
        labelingState++;
        break; }
    case 5: {
        tempSavedPoints[3] = point;
        drawCircle(point, gTempItems, "circle4");

        QGraphicsPathItem *path = modifyOrNew<QGraphicsPathItem>(gTempItems, "path");
        path->setPath(createPath(tempSavedPoints, 4));
        QPainterPath k = QPainterPath(path->path());
        k.closeSubpath();
        path->setPath(k);

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
            // mouseClickImage(tempSavedPoints[3]);
            this->save();
        }
        break;
    }
}

void ImageLabelingScene::save()
{
    if ((labelingState % totalStates) == 5) {
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
        currentLabeledImage->setBbox(pair, int(labelingState/totalStates));

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

        emit bRectDone();
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



LabeledImage* ImageLabelingScene::changeImage(LabeledImage &labeledImage)
{
    if (currentLabeledImage != nullptr)
    {
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

        LabeledImage* oldImage = currentLabeledImage;
        this->removeItem(oldImage);

        currentLabeledImage = &labeledImage;
        this->addItem(currentLabeledImage);

        return oldImage;
    } else {
        currentLabeledImage = &labeledImage;
        this->addItem(currentLabeledImage);

        emit newInstruction("Select top-left side of the bounding rectangle around an object in the image","");
        return nullptr;
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

QGraphicsEllipseItem* ImageLabelingScene::drawCircle(QPointF point, QMap<QString, QGraphicsItem*> &map, QString name) {
    QGraphicsEllipseItem *circle = modifyOrNew<QGraphicsEllipseItem>(map, name);
    circle->setRect(QRectF(point.x()-2, point.y()-2,4.,4.));
    return circle;
}
void ImageLabelingScene::drawCrosshairs(QPointF point, QMap<QString, QGraphicsItem*> &map, QString name, int length, QPen style) {
    QRectF bounds = QRectF(QPointF(0,0), QSizeF(this->currentLabeledImage->width, this->currentLabeledImage->height));
    QPointF left, right, top, bot;
    if (length <= -1) {
        left = QPointF(0,point.y());
        right = QPointF(bounds.width(), point.y());

        top = QPointF(point.x(), 0);
        bot = QPointF(point.x(), bounds.height());
    } else {
        left = point + QPointF(-length/2.,0);
        if ( left.x() < 0.) left = QPointF(0, point.y());
        right = point + QPointF(length/2.,0);
        if ( right.x() > bounds.width()) right = QPointF(bounds.width(),point.y());
        top = point + QPointF(0,-length/2.);
        if ( top.y() < 0.) top = QPointF(point.x(), 0);
        bot = point + QPointF(0, length/2.);
        if ( bot.y() > bounds.height()) bot = QPointF(point.x(),bounds.height());
    }
    QGraphicsLineItem* horiz = modifyOrNew<QGraphicsLineItem>(map, QString("horizontalLine").append(name));
    horiz->setLine(QLineF(left, right));
    horiz->setPen(style);

    QGraphicsLineItem* vert = modifyOrNew<QGraphicsLineItem>(map, QString("verticalLine").append(name));
    vert->setLine(QLineF(top, bot));
    vert->setPen(style);
    return;
}
