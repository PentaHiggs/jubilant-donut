#ifndef LABELEDIMAGE_H
#define LABELEDIMAGE_H

#include <QString>
#include <QPixmap>
#include <QVector>
#include <QUrl>
#include <QGraphicsPixmapItem>
#include <QGraphicSceneHoverEvent>

typedef struct
{
    /*
     * typedef for a bounding box structure for objects in an image.
     * x, y are coordinates of bottom left corner.
     * w, h are width and height, respectively, in pixels.
     */
   int x;
   int y;
   int w;
   int h;
} bRect;


typedef struct
{
    /*
     * typedef for for a linear transformation of a bRect in projective space, where
     * homogenous coordinates are being used.
     *
     */
    int m11;
    int m12;
    int m13;
    int m21;
    int m22;
    int m23;
    int m31;
    int m32;
    int m33;
} bRectTransform;

class LabeledImage : public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    LabeledImage();
    ~LabeledImage();
    QString label;
    QVector< std::pair<bRect, bRectTransform> > *bBoxes;
    int width;
    int height;
signals:
    void mouseEnterImage(QPointF point);
    void mouseMoveOnImage(QPointF point);
    void mouseLeaveImage();
    void mouseClickImage(QPointF point);

protected:
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event);

    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

}

#endif // LABELEDIMAGE_H
