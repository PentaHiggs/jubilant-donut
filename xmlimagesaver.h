#ifndef XMLIMAGESAVER_H
#define XMLIMAGESAVER_H

#include <QXmlStreamWriter>
#include <QUrl>
#include <QIODevice>

class XmlImageSaver
{
public:
    XmlImageSaver(QIODevice*, QUrl);

    void saveXml();
    void toXml(LabeledImage*);
private:
    QXmlStreamWriter* writer;
};

#endif // XMLIMAGESAVER_H
