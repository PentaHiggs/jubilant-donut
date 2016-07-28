#ifndef IMAGELABELLINGSCENE_H
#define IMAGELABELLINGSCENE_H

#include <QGraphicsScene>
#include <QPoint>
#include "labeledimage.h"

class ImageLabellingScene : public QGraphicsScene
{
    Q_OBJECT;
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
    QGraphicsLineItem *line1;
    QGraphicsLineItem *line2;

};

#endif // IMAGELABELLINGSCENE_H
