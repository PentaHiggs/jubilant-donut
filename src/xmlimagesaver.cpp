#include "xmlimagesaver.h"
#include "labeledimage.h"

#include <QString>
#include <QFileDialog>
#include <QDebug>

XmlImageSaver::XmlImageSaver()
{
    temp.open();
    writer.setDevice(&temp);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeDTD("<!DOCTYPE picture_batch>");
    writer.writeStartElement("picture_batch");
    qDebug() << "XmlImageSaver :16";
}


XmlImageSaver::~XmlImageSaver()
{
}

void XmlImageSaver::saveXml()
{
    writer.writeEndElement(); // /picture_batch
    writer.writeEndDocument();
    QString filename = QFileDialog::getSaveFileName(
                0,
                QString("Save XML File"),
                QString(""),
                QString("XML File (*.xml)"));
    QFile file(filename);
    file.open( QIODevice::WriteOnly );
    qDebug() << "33: xmlimagesaver.cpp";
    QByteArray buffer;
    int chunkSize = 100;
    temp.seek(0); // We can't forget to go back to beginning of temp file, or else no reading occurs
    while ( !((buffer = temp.read(chunkSize)).isEmpty()))
    {
        file.write(buffer);
        qDebug() << "39: xmlimagesaver.cpp";
    }
    temp.close();
    file.close();
}

void XmlImageSaver::toXml(LabeledImage const* img)
{
    writer.writeStartElement("picture");
    writer.writeTextElement("label",img->label);
    writer.writeTextElement("resource_url",img->url);

    writer.writeStartElement("bounding_boxes");
    for (const std::pair<bRect, bRectTransform> &box : *(img->bBoxes)) {
        qDebug() << "55: xmlImageSaver.cpp";
        writer.writeStartElement("bounding_box");

        writer.writeStartElement("bounding_rect");
        writer.writeTextElement("x", QString::number(box.first.x));
        writer.writeTextElement("y", QString::number(box.first.y));
        writer.writeTextElement("w", QString::number(box.first.w));
        writer.writeTextElement("h", QString::number(box.first.h));
        writer.writeEndElement(); // /bounding_rect

        writer.writeStartElement("brect_transform");
        writer.writeTextElement("m11", QString::number(box.second.m11));
        writer.writeTextElement("m12", QString::number(box.second.m12));
        writer.writeTextElement("m13", QString::number(box.second.m13));
        writer.writeTextElement("m21", QString::number(box.second.m21));
        writer.writeTextElement("m22", QString::number(box.second.m22));
        writer.writeTextElement("m23", QString::number(box.second.m23));
        writer.writeTextElement("m31", QString::number(box.second.m31));
        writer.writeTextElement("m32", QString::number(box.second.m32));
        writer.writeTextElement("m33", QString::number(box.second.m33));
        writer.writeEndElement(); // /brect_transform

        writer.writeEndElement(); // /bounding_box
    }
    writer.writeEndElement(); // /bounding_boxes

    writer.writeEndElement(); // /picture
    return;
}
