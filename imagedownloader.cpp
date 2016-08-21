#include "imagedownloader.h"
#include <QTimer>
#include <QEventLoop>
#include <QNetworkRequest>
#include <QNetworkReply>

ImageDownloader::ImageDownloader(QObject *parent)
{
   nManager = new QNetworkAccessManager(parent);
}

ImageDownloader::~ImageDownloader() {
   delete nManager;
}

QPixmap ImageDownloader::download(QUrl imageUrl) {
    QTimer timer;
    QEventLoop loop;

    timer.setSingleShot(true);

    QObject::connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    QObject::connect(nManager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));

    QNetworkRequest request(imageUrl);
    QNetworkReply *reply = nManager->get(request);

    timer.start(10000); // 20 second timeout
    loop.exec();

    QPixmap img = QPixmap();
    if (timer.isActive()){
        // success!
        QByteArray data = reply->readAll();
        img.loadFromData(data);
        qDebug() << "Image successfully loaded from url " << imageUrl;
    } else {
        // failure : <
        qDebug() << "Image loading from url" << imageUrl << "failed.";
    }
    return img;
}
