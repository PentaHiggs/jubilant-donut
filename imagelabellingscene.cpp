#include "imagelabellingscene.h"

ImageLabellingScene::ImageLabellingScene() :
    labellingState(0),
    line1(nullptr),
    line2(nullptr)
{
    QGraphicsScene::QGraphicsScene();

}

ImageLabellingScene::ImageLabellingScene(LabeledImage labeledImage) :
    labeledImage(labeledImage)
{

    ImageLabellingScene();
}

ImageLabellingScene::~ImageLabellingScene() {
    delete line1;
    delete line2;
    QGraphicsScene::~QGraphicsScene();
}

void ImageLabellingScene::mouseEnterImage(QPointF point)
{
    if(labellingState==0 || labellingState==1) {
        // Make a horizontal line going through point
        line1 = new QGraphicsLineItem(QLineF(point, point+QPointF(1,0)));

        // Make a verticla line going through point
        line2 = new QGraphicsLineItem(QLineF(point, point+QPointF(0,1)));
    } else if (labellingState >= 2 && labellingState <= 5){
        // We have a skew dot following the cursor instead now!
    }
}

void ImageLabellingScene::mouseMoveOnImage(QPointF point)
{
    // we setLine here
}

void ImageLabellingScene::mouseLeaveImage()
{

}

void ImageLabellingScene::mouseClickImage(QPointF point)
{

}

void ImageLabellingScene::forward()
{

}

void ImageLabellingScene::back()
{
    // Left unimplemented for now
}
