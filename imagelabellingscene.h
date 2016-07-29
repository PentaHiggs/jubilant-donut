#ifndef IMAGELABELLINGSCENE_H
#define IMAGELABELLINGSCENE_H

#include <QGraphicsScene>
#include <QPoint>
#include <QMap>
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
    void solidifyLines();
    int labellingState;

    QMap<QString, *QGraphicsItem> gTempItems;
    QMap<QString, *QGraphicsItem> gPermItems;
};

#endif // IMAGELABELLINGSCENE_H
