#ifndef IMAGEDOWNLOADER_H
#define IMAGEDOWNLOADER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QPixmap>

class ImageDownloader : public QObject
{
    Q_OBJECT
public:
    explicit ImageDownloader(QUrl imageUrl, QObject *parent = 0);
    virtual ~ImageDownloader();
    QPixmap downloadedImage() const;

signals:
    void downloaded();
public slots:
    void imageDownloaded(QNetworkReply* pReply);
private:
    QNetworkAccessManager m_WebCtrl;
    QByteArray m_DownloadedImageData;
};

#endif // IMAGEDOWNLOADER_H
