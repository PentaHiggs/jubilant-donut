#ifndef XMLIMAGELOADER_H
#define XMLIMAGELOADER_H

#include <utility>

#include <QUrl>
#include <QString>
#include <QPixmap>
#include <QVector>
#include <QXmlStreamReader>
#include <QObject>

#include "labeledimage.h"
#include "imagedownloader.h"

class XmlImageLoader : public QObject
{
    Q_OBJECT

public:
    XmlImageLoader(QIODevice *device);
    XmlImageLoader();
    virtual ~XmlImageLoader();
    QString errorString() const;
    LabeledImage *next();
signals:
    void setImgNo(int, QString);
private:
    int currentImgNo;
    QXmlStreamReader xml;
    ImageDownloader *imgDownloader;
    LabeledImage *loadPicture();
    loadBoundingBoxes(LabeledImage *img);
};

#endif // XMLIMAGELOADER_H
