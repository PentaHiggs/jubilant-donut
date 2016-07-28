

#include <memory>

#include <QUrl>

#include "xmlimageloader.h"
#include "labeledimage.h"
#include "imagedownloader.h"

XmlImageLoader::XmlImageLoader(QIODevice *xmlFile)
{
    xml = QXmlStreamReader(xmlFile);
    imgDownloader = ImageDownloader();
    xml.setDevice(xmlFile);

    // This variable is increased by 1 every time we read a labeledImage
    currentImgNo = -1;

    if (xml.readNextStartElement()) {
        if (xml.name() == "picture_batch") {
            // We're good to go!
        }
        else
            xml.raiseError(QObject::tr("The file is not a picture_batch file"));
    }
    return !xml.error();

}

LabeledImage *XmlImageLoader::next() {
    // Find the next <picture> element.
    while(xml.readNextStartElement() && !xml.name() == "picture")
        xml.skipCurrentElement();
    return loadPicture(img);
}

XmlImageLoader::errorString() const
{
    return QObject::tr("%1\nLine %2, column %3")
            .arg(xml.errorString())
            .arg(xml.lineNumber())
            .arg(xml.columnNumber());
}

LabeledImage* XmlImageLoader::loadPicture(){
    std::shared_ptr<LabeledImage> img = new LabeledImage();
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
        img->setPixmap(pixmap);
    } else {
        return nullptr;
    }
    xml.readNextStartElement();
    if (xml.name() == "bounding_boxes")
    {
        while( xml.readNextStartElement() && (xml.name() == "bounding_box") )
        {
            std::pair<bRect, bRectTransform> pair;
            bRect bRec;
            bRectTransform bTrans;

            xml.readNextStartElement();
            if (xml.name() != "bounding_rect") return nullptr;
            xml.readNextStartElement(); // <x>
            bRec.x = xml.readElementText().toInt();
            xml.readNextStartElement(); // <y>
            bRec.y = xml.readElementText().toInt();
            xml.readNextStartElement(); // <w>
            bRec.w = xml.readElementText().toInt();
            xml.readNextStartElement(); // <h>
            bRec.h = xml.readElementText().toInt();

            xml.readNextStartElement();
            if (xml.name() != "shear_rect") return nullptr;
            xml.readNextStartElement(); // <dx>
            bTrans.x = xml.readElementText().toInt();
            xml.readNextStartElement(); // <dy>
            bTrans.y = xml.readElementText().toInt();
            xml.readNextStartElement(); // <m11>
            bTrans.w = xml.readElementText().toInt();
            xml.readNextStartElement(); // <m12>
            bTrans.h = xml.readElementText().toInt();
            xml.readNextStartElement(); // <m21>
            bTrans.w = xml.readElementText().toInt();
            xml.readNextStartElement(); // <m22>
            bTrans.h = xml.readElementText().toInt();

            pair = std::make_pair(bRec, bTrans);
            img->bBoxes->append(pair);
        }

    }
    currentImgNo++;
    return img;
}
