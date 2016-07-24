#include "imagedownloader.h"
#include <QTimer>
#include <QEventLoop>
#include <QNetworkRequest>
#include <QNetworkReply>

ImageDownloader::ImageDownloader(QObject *parent = 0)
{
   nManager = new QNetworkAccessManager(parent);
}

ImageDownloader::~ImageDownloader() {
   delete nManager;
}

ImageDownloader::download(QUrl imageUrl) {
    QTimer timer;
    QEventLoop loop;

    t.setSingleShot(true);

    connect(&timer, SIGNAL(timeout()), &loop, SLOT(quit()));
    connect(&nManager, SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));

    QNetworkRequest request(imageUrl);
    QNetworkReply *reply = nManager.get(request);

    timer.start(10000); // 20 second timeout
    loop.exec();

    QPixmap img = QPixmap(parent);
    if (t.isActive()){
        // success!
        data = reply->readAll();
        QPixmap img = QPixmap(parent);
        img.loadFromData(data);
        return img;
    } else {
        // failure : <
        return img;
    }
}
