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
    void changeImage(LabeledImage &labeledImage);
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
    void skewDone();
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
    void saveCurrent();

    template<typename T> T* modifyOrNew(QMap<QString, QGraphicsItem*> &, QString);
    void deleteItem(QMap<QString, QGraphicsItem*> &, QString);
};

#endif // IMAGELABELINGSCENE_H
