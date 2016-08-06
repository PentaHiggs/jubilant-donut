#include "labeledimage.h"



LabeledImage::LabeledImage() : QGraphicsPixmapItem()
{
    setAcceptHoverEvents(true);
}

LabeledImage::~LabeledImage() {
    delete bBoxes;
}

void LabeledImage::hoverEnterEvent(QGraphicsSceneHoverEvent *event){
    emit mouseEnterImage(event->scenePos());
    QGraphicsPixmapItem::hoverEnterEvent(event);
}

void LabeledImage::hoverMoveEvent(QGraphicsSceneHoverEvent *event){
    emit mouseMoveOnImage(event->scenePos());
    QGraphicsPixmapItem::hoverMoveEvent(event);
}

void LabeledImage::hoverLeaveEvent(QGraphicsSceneHoverEvent *event){
    emit mouseLeaveImage();
    QGraphicsPixmapItem::hoverLeaveEvent(event);
}

void LabeledImage::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    emit mouseClickImage(event->scenePos());
    QGraphicsPixmapItem::mouseReleaseEvent(event);
}

bRectTransform LabeledImage::findRectTransform(bRect R, QPoint A, QPoint B, QPoint C, QPoint D){
    /*(
    Eigen::Matrix<float, 8, 8> k;
    k <<    R.x,    R.y,    1,      0,      0,      0,      (-1)*R.x*A.x(),         (-1)*R.y*A.x(),
            0,      0,      0,      R.x,    R.y,    1,      (-1)*R.x*A.y(),         (-1)*R.y*A.y(),
            R,x,    R.y+R.h,1,      0,      0,      0,      (-1)*R.x*B.x(),         (-1)*(R.y+R.h)*B.x(),
            0,      0,      0,      R.x,    R.y+R.h,1,      (-1)*R.x*B.y(),         (-1)*(R.y+R.h)*B.y(),
            R.x+R.w,R.y+R.h,1,      0,      0,      0,      (-1)*(R.x+R.w)*C.x(),   (-1)*(R.y+R.h)*C.x(),
            0,      0,      0,      R.x+R.w,R.y+R.h,1,      (-1)*(R.x+R.w)*C.y(),   (-1)*(R.y+R.h)*C.y(),
            R.x+R.w,R.y,    1,      0,      0,      0,      (-1)*(R.x+R.w)*D.x(),   (-1)*R.y*D.x(),
            0,      0,      0,      R.x+R.w,R.y,    1,      (-1)*(R.x+R.w)*D.y(),   (-1)*R.y*D.y();

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
    */
    return bRectTransform();
}
