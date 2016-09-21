#include "labeledimage.h"
#include <Eigen/Dense>
#include <QtDebug>
#include "projectivetransform.h"
#include <array>
#include <utility>

LabeledImage::LabeledImage() : QGraphicsPixmapItem()
{
    setAcceptHoverEvents(true);
    bBoxes = new QVector< std::pair<bRect, bRectTransform> >();
}

LabeledImage::~LabeledImage() {
    delete bBoxes;
}

void LabeledImage::setImage(QPixmap& pix, QString& url) {
    this->setPixmap(pix);
    this->url = url;
    this->width = pix.width();
    this->height = pix.height();
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

void LabeledImage::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    emit mouseClickImage(event->scenePos());
    QGraphicsPixmapItem::mousePressEvent(event);
}

void LabeledImage::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsPixmapItem::mouseReleaseEvent(event);
}

bRectTransform LabeledImage::findRectTransform(bRect R, QPoint A, QPoint B, QPoint C, QPoint D){

    std::array<std::pair<int,int>,4> in{
            std::pair<int,int>(A.x(), A.y()),
            std::pair<int,int>(B.x(), B.y()),
            std::pair<int,int>(C.x(), C.y()),
            std::pair<int,int>(D.x(), D.y())
            };
    std::array<std::pair<int,int>,4> out{
            std::pair<int,int>(R.x, R.x+R.w),
            std::pair<int,int>(R.x+R.w, R.y),
            std::pair<int,int>(R.x+R.w, R.y+R.h),
            std::pair<int,int>(R.x, R.y+R.h)
    };

    std::array<float,9> m = projectiveTransform(in, out);

    bRectTransform b;
    b.m11 = m[0];
    b.m12 = m[1];
    b.m13 = m[2];
    b.m21 = m[3];
    b.m22 = m[4];
    b.m23 = m[5];
    b.m31 = m[6];
    b.m32 = m[7];
    b.m33 = m[8];
    return b;
}
void LabeledImage::setBbox(std::pair<bRect, bRectTransform> box, int index){
    if (index < this->bBoxes->size()) {
        this->bBoxes->replace(index, box);
    } else {
        this->bBoxes->append(box);
    }
}
