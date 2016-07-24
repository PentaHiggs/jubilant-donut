#ifndef XMLIMAGELOADER_H
#define XMLIMAGELOADER_H

#include <pair>

#include <QUrl>
#include <QString>
#include <QPixmap>
#include <QVector>
#include <QXmlStreamReader>

typedef struct
{
    /*
     * struct containing a vector of bounding boxes, and linearly transformed
     * and translated boxes; an image, image label, and image width/height
     * */
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

    // width & height of image
    int width;
    int height;

    QString label;
    QPixmap image;
    QVector< std::pair<bRect, bRectTransform> > bBoxes;
    QUrl resourceUrl;

} cImage;

class XmlImageLoader
{
public:

    QString errorString() const;
private:
    QXmlStreamReader xml;
    XmlImageLoader(QUrl resource);
    QIODevice xmlFile;
};

#endif // XMLIMAGELOADER_H
