#ifndef IMAGEDOWNLOADER_H
#define IMAGEDOWNLOADER_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QPixmap>

class ImageDownloader
{
public:
    ImageDownloader(QObject *parent = 0);
   ~ImageDownloader();
    QPixmap download(QUrl url);
private:
    QNetworkAccessManager nManager;
};

#endif // IMAGEDOWNLOADER_H
