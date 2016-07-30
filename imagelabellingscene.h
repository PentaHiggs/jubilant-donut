#ifndef IMAGELABELLINGSCENE_H
#define IMAGELABELLINGSCENE_H

#include <QGraphicsScene>
#include <QPoint>
#include <QMap>
#include <QVector>

#include "labeledimage.h"

class ImageLabellingScene : public QGraphicsScene
{
    Q_OBJECT
public:
    ImageLabellingScene();
    ImageLabellingScene(LabeledImage labeledImage);
    ~ImageLabellingScene();

public slots:
    void mouseEnterImage(QPointF point);
    void mouseMoveOnImage(QPointF point);
    void mouseLeaveImage();
    void mouseClickImage(QPointF point);
    void forward();
    void back();
signals:
    void skewDone();
private:
    LabeledImage currentLabeledImage;

    int labellingState;

    QMap<QString, *QGraphicsItem> gMouseoverItems;
    QMap<QString, *QGraphicsItem> gTempItems;
    QVector<*QGraphicsItem> gPermItems;
};

#endif // IMAGELABELLINGSCENE_H
