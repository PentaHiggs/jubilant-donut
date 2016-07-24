#ifndef LABELEDIMAGE_H
#define LABELEDIMAGE_H

#include <QString>
#include <QPixmap>
#include <QVector>
#include <QUrl>

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
     * typedef for an affine linear trnsformation of a bRect, with the transformation
     * [[m11, m12],[m21,m22]] * x + [[dx],[dy]]
     * dx and dy are the translation coordinates
     * m11, m12, m21, m22 are the matrix elements of a linear transformation
     */
    int dx;
    int dy;
    int m11;
    int m12;
    int m21;
    int m22;
} bRectTransform;

class labeledImage
{
public:
    labeledImage();
    QString label;
    QPixmap image;
    QVector< std::pair<bRect, bRectTransform> > bBoxes;
    int width;
    int height;
}

#endif // LABELEDIMAGE_H
