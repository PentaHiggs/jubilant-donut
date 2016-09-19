#ifndef XMLIMAGESAVER_H
#define XMLIMAGESAVER_H

#include <QXmlStreamWriter>
#include <QUrl>
#include <QIODevice>
#include <QTemporaryFile>

#include "labeledimage.h"

class XmlImageSaver
{
public:
    XmlImageSaver();
    ~XmlImageSaver();

    void saveXml();
    void toXml(LabeledImage const*);
private:
    QXmlStreamWriter writer;
    QTemporaryFile temp;
};

#endif // XMLIMAGESAVER_H
