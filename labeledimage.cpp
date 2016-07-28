#include "labeledimage.h"



LabeledImage::LabeledImage()
{
    QGraphicsPixmapItem::QGraphicsPixmapItem();
    this->setAttribute(Qt::WA_Hover, true);
    setAcceptHoverEvents(true);
}

LabeledImage::~LabeledImage() {
    delete bBoxes;
    QGraphicsPixmapItem::~QGraphicsPixmapItem();
}

virtual void LabeledImage::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    emit mouseEnterImage(event->scenePos());
    QGraphicsPixmapItem::hoverEnterEvent(event);
}

virtual void LabeledImage::hoverMoveEvent(QGraphicsSceneHoverEvent *event){
    emit mouseMoveOnImage(event->scenePos());
    QGraphicsPixmapItem::hoverMoveEvent(event);
}

virtual void LabeledImage::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    emit mouseLeaveImage();
    QGraphicsPixmapItem::hoverLeaveEvent(event);
}

virtual void LabeledImage::mouseReleaseEvent(QGraphicsSceneHoverEvent *event){
    emit mouseClickImage(event->scenePos());
    QGraphicsPixmapItem::mouseReleaseEvent(event);
}

bRectTransform LabeledImage::setRectTransform(QPoint A, QPoint B, QPoint C, QPoint D){
    Eigen::Matrix<float, 8, 8> k;
    k <<    0,  0,  1,  0,  0,  0,  0,          0,
            0,  0,  0,  0,  0,  1,  0,          0,
            0,  1,  1,  0,  0,  0,  0,          (-1)*B.x(),
            0,  0,  0,  0,  1,  1,  0,          (-1)*B.y(),
            1,  1,  1,  0,  0,  0,  (-1)*C.x(), (-1)*C.x(),
            0,  0,  0,  1,  1,  1,  (-1)*C.y(), (-1)*C.y(),
            1,  0,  1,  0,  0,  0,  (-1)*D.x(), 0,
            0,  0,  0,  1,  0,  1,  (-1)*D.y(), 0;

    Eigen::Matrix<float, 8, 8> inverseK;
    bool invertible;
    double determinant;
    k.computeInverseAndDetWithCheck(inverseK, determinant, invertible);
    Eigen::Matrix<float, 8, 1> u;
    u <<    A.x(), A.y(), B.x(), B.y(),
            C.x(), C.y(), D.x(), D.y();
    Eigen::Matrix<float, 8, 1> M;
    M = inverseK * u;
    bRectTransform B;
    B.m11 = M(0,0);
    B.m12 = M(1,0);
    B.m13 = M(2,0);
    B.m21 = M(3,0);
    B.m22 = M(4,0);
    B.m23 = M(5,0);
    B.m31 = M(6,0);
    B.m32 = M(7,0);
    B.m33 = 1.;
    return B;
}
