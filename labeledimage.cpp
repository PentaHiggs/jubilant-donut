#include "labeledimage.h"
#include <Eigen/Dense>


LabeledImage::LabeledImage() : QGraphicsPixmapItem()
{
    setAcceptHoverEvents(true);
}

LabeledImage::~LabeledImage() {
    delete bBoxes;
}

void LabeledImage::setImage(QPixmap& pix, QString& url) {
    this->setPixmap(pix);
    this->url = url;
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

    int x1 = R.x; int x2 = R.x; int x3 = R.x+R.w; int x4 = R.x+R.w;
    int y1 = R.y; int y2 = R.y+R.h; int y3 = R.y+R.h; int y4 = R.y;

    Eigen::Matrix<float, 8, 9> M;
    M <<    x1,     y1,     1,      0,      0,      0,      (-1)*x1*A.x(),  (-1)*y1*A.x(),  (-1)*A.x(),
            0,      0,      0,      x1,     y1,     1,      (-1)*x1*A.y(),  (-1)*y1*A.y(),  (-1)*A.y(),
            x2,     y2,     1,      0,      0,      0,      (-1)*x2*B.x(),  (-1)*y2*B.x(),  (-1)*B.x(),
            0,      0,      0,      x2,     y2,     1,      (-1)*x2*B.y(),  (-1)*y2*B.y(),  (-1)*B.y(),
            x3,     y3,     1,      0,      0,      0,      (-1)*x3*C.x(),  (-1)*y3*C.x(),  (-1)*C.x(),
            0,      0,      0,      x3,     y3,     1,      (-1)*x3*C.y(),  (-1)*y3*C.y(),  (-1)*C.y(),
            x4,     y4,     1,      0,      0,      0,      (-1)*x4*D.x(),  (-1)*y4*D.x(),  (-1)*D.x(),
            0,      0,      0,      x4,     y4,     1,      (-1)*x4*D.y(),  (-1)*y4*D.y(),  (-1)*D.y();

    Eigen::Matrix<float, 8, 1> z;
    z << 0, 0, 0, 0, 0, 0, 0, 0;

    Eigen::Matrix<float, 9, 1> sol = M.colPivHouseholderQr().solve(z);

    // Going to normalize the entries of the matrix as a vector
    Eigen::Matrix<float, 9, 1> m = sol.normalized();

    bRectTransform b;
    b.m11 = m(0,0);
    b.m12 = m(1,0);
    b.m13 = m(2,0);
    b.m21 = m(3,0);
    b.m22 = m(4,0);
    b.m23 = m(5,0);
    b.m31 = m(6,0);
    b.m32 = m(7,0);
    b.m33 = m(8,0);

    return b;
    //return bRectTransform();
}
