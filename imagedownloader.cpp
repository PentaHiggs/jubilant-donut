#include "imagedownloader.h"

ImageDownloader::ImageDownloader(QUrl imageUrl, QObject *parent) : QObject(parent)
{
    connect(
        &m_WebCtrl,
        SIGNAL (finished(QNetworkReply*)),
        this,
        SLOT (imageDownloaded(QNetworkReply*))
        );

    QNetworkRequest request(imageUrl);
    m_WebCtrl.get(request);
}

ImageDownloader::~ImageDownloader() { }

void ImageDownloader::imageDownloaded(QNetworkReply* pReply) {
    m_DownloadedImageData = pReply->readAll();

    pReply -> deleteLater();
    emit downloaded();
}

QPixmap ImageDownloader::downloadedImage() const {
    QPixmap img;
    img.loadFromData(m_DownloadedImageData);
    return img;
}
