

#include <memory>

#include <QUrl>

#include "xmlimageloader.h"
#include "labeledimage.h"
#include "imagedownloader.h"

XmlImageLoader::XmlImageLoader(QIODevice *xmlFile)
{
    imgDownloader = ImageDownloader();
    xml.setDevice(xmlFile);

    if (xml.readNextStartElement()) {
        if (xml.name() == "picture_batch")
            while(xml.readNextStartElement()){
                if (xml.name() == "picture" )
                {
                    std::shared_ptr<labeledImage> img = new labeledImage();
                    loadPicture(img);
                }
                else
                    xml.skipCurrentElement();
            }
        else
            xml.raiseError(QObject::tr("The file is not a picture_batch file"));
    }
    return !xml.error();
}

XmlImageLoader::errorString() const
{
    return QObject::tr("%1\nLine %2, column %3")
            .arg(xml.errorString())
            .arg(xml.lineNumber())
            .arg(xml.columnNumber());
}

XmlImageLoader::loadPicture(labeledImage *img){
    xml.readNextStartElement();
    if (xml.name() == "label")
    {
        label = xml.readElementText();
        img->label = label;
    } else
        return nullptr;

    xml.readNextStartElement();
    if (xml.name() == "resource_url")
    {
        resUrlText = xml.readElementText();
        resUrl = QUrl(resUrlText);
        QPixmap pixmap = imgDownloader.download(resUrlText);
        img->image = pixmap;
    } else {
        return nullptr;
    }

    xml.readNextStartElement();
    if (xml.name() == "bounding_boxes")
    {
        QVector< std::pair<bRect, bRectTransform> > list = QVector();

        while( xml.readNextStartElement() && (xml.name() == "bounding_box") )
        {
            std::pair<bRect, bRectTransform> pair;
            bRect bRec;
            bRectTransform bTrans;

            xml.readNextStartElement();
            if (xml.name() != "bounding_rect") return nullptr;
            xml.readNextStartElement(); // <x>
            bRec.x = std::stoi(xml.readElementText);
            xml.readNextStartElement(); // <y>
            bRec.y = std::stoi(xml.readElementText);
            xml.readNextStartElement(); // <w>
            bRec.w = std::stoi(xml.readElementText);
            xml.readNextStartElement(); // <h>
            bRec.h = std::stoi(xml.readElementText);

            xml.readNextStartElement();
            if (xml.name() != "shear_rect") return nullptr;
            xml.readNextStartElement(); // <dx>
            bTrans.x = std::stoi(xml.readElementText);
            xml.readNextStartElement(); // <dy>
            bTrans.y = std::stoi(xml.readElementText);
            xml.readNextStartElement(); // <m11>
            bTrans.w = std::stoi(xml.readElementText);
            xml.readNextStartElement(); // <m12>
            bTrans.h = std::stoi(xml.readElementText);
            xml.readNextStartElement(); // <m21>
            bTrans.w = std::stoi(xml.readElementText);
            xml.readNextStartElement(); // <m22>
            bTrans.h = std::stoi(xml.readElementText);

            pair = std::make_pair(bRec, bTrans);
            list.append(pair);
        }
    }
}
