#ifndef XMLIMAGELOADER_H
#define XMLIMAGELOADER_H

#include <utility>

#include <QUrl>
#include <QString>
#include <QPixmap>
#include <QVector>
#include <QXmlStreamReader>

#include "labeledimage.h"
#include "imagedownloader.h"

class XmlImageLoader
{
public:
    XmlImageLoader(QIODevice *device, QUrl uri);
    ~XmlImageLoader();
    QString errorString() const;
    LabeledImage *next();
private:
    int currentImgNo;
    QXmlStreamReader xml;
    ImageDownloader *imgDownloader;
    LabeledImage *loadPicture();
    loadBoundingBoxes(LabeledImage *img);
};

#endif // XMLIMAGELOADER_H
