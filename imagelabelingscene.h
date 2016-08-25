#ifndef IMAGELABELINGSCENE_H
#define IMAGELABELINGSCENE_H

#include <QGraphicsScene>
#include <QPoint>
#include <QMap>
#include <QVector>

#include "labeledimage.h"

class ImageLabelingScene : public QGraphicsScene
{
    Q_OBJECT

public:
    ImageLabelingScene();
    ImageLabelingScene(LabeledImage &labeledImage);
    LabeledImage* changeImage(LabeledImage &labeledImage);
    ~ImageLabelingScene();

public slots:
    void mouseEnterImage(QPointF point);
    void mouseMoveOnImage(QPointF point);
    void mouseLeaveImage();
    void mouseClickImage(QPointF point);
    void forward();
    void back();
    void save();

signals:
    void bRectDone();
    void newInstruction(QString longStr, QString shortStr, bool isBack=false);
private:
    LabeledImage *currentLabeledImage;

    int labelingState;
    int const totalStates = 6;

    QPointF tempSavedPoints[4];

    QMap<QString, QGraphicsItem*> gMouseoverItems;
    QMap<QString, QGraphicsItem*> gTempItems;
    QVector<QGraphicsItem*> gPermItems;

    bRect currentBox;

    template<typename T> T* modifyOrNew(QMap<QString, QGraphicsItem*> &, QString);
    void deleteItem(QMap<QString, QGraphicsItem*> &, QString);
    QGraphicsEllipseItem* drawCircle(QPointF point, QMap<QString, QGraphicsItem*> &map, QString name);
    void drawCrosshairs(QPointF point, QMap<QString, QGraphicsItem*> &map, QString name=QString(), int length=-1, QPen style=QPen());
};

#endif // IMAGELABELINGSCENE_H
