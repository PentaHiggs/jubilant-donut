#include <memory>

#include <QUrl>
#include <QXmlSchemaValidator>
#include <QXmlStreamReader>
#include <QXmlSchema>

#include "xmlimageloader.h"
#include "labeledimage.h"
#include "imagedownloader.h"

XmlImageLoader::XmlImageLoader(QIODevice *xmlFile, QUrl uri)
{
    imgDownloader = new ImageDownloader();
    xml.setDevice(xmlFile);

    QUrl schemaUrl(":/picture_batch.xsd");
    QXmlSchema schema;
    schema.load(schemaUrl);
    if (schema.isValid()) {
        QXmlSchemaValidator validator(schema);
        if (validator.validate(xmlFile, uri)) {
            qDebug() << "Loaded xml" << uri.fileName() << "is valid";
            // This variable is increased by 1 ever time we read a labeledImage
            currentImgNo = -1;
            do xml.readNextStartElement();
            while (xml.name() != "picture_batch");
        } else {
            xml.raiseError(QObject::tr("The file is not a valid picture_batch file"));
            return;
        }
    } else {
        qDebug() << "invalid schema file, please fix!";
    }
}

XmlImageLoader::~XmlImageLoader(){
    delete imgDownloader;
}

LabeledImage *XmlImageLoader::next() {
    // Find the next <picture> element.
    while(xml.readNextStartElement() && !(xml.name() == "picture"))
        xml.skipCurrentElement();
    return loadPicture();
}

LabeledImage* XmlImageLoader::loadPicture(){
    LabeledImage *img =  new LabeledImage();
    xml.readNextStartElement();
    if (xml.name() == "label")
    {
        QString label = xml.readElementText();
        img->label = label;
    } else
        return nullptr;

    xml.readNextStartElement();
    if (xml.name() == "resource_url")
    {
        QString resUrlText = xml.readElementText();
        QUrl resUrl(resUrlText);
        QPixmap pixmap = imgDownloader->download(resUrlText);
        img->setImage(pixmap, resUrlText);
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
            if (xml.name() != "brect_transform") return nullptr;
            xml.readNextStartElement(); // <m11>
            bTrans.m11 = xml.readElementText().toInt();
            xml.readNextStartElement(); // <m12>
            bTrans.m12 = xml.readElementText().toInt();
            xml.readNextStartElement(); // <m13>
            bTrans.m13 = xml.readElementText().toInt();
            xml.readNextStartElement(); // <m21>
            bTrans.m21 = xml.readElementText().toInt();
            xml.readNextStartElement(); // <m22>
            bTrans.m22 = xml.readElementText().toInt();
            xml.readNextStartElement(); // <m23>
            bTrans.m23 = xml.readElementText().toInt();
            xml.readNextStartElement(); // <m31>
            bTrans.m31 = xml.readElementText().toInt();
            xml.readNextStartElement(); // <m32>
            bTrans.m32 = xml.readElementText().toInt();
            xml.readNextStartElement(); // <m33>
            bTrans.m33 = xml.readElementText().toInt();

            pair = std::make_pair(bRec, bTrans);
            img->bBoxes->append(pair);
        }

    }
    currentImgNo++;
    emit setImgNo(currentImgNo, img->label);
    return img;
}
