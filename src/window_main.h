#ifndef WINDOW_MAIN_H
#define WINDOW_MAIN_H

#include <QMainWindow>

#include <memory>
#include <QString>

#include "xmlimageloader.h"
#include "imagelabelingscene.h"
#include "xmlimagesaver.h"

namespace Ui {
class window_main;
}

class window_main : public QMainWindow
{
    Q_OBJECT

public:
    explicit window_main(QWidget *parent = 0);
    ~window_main();

private slots:
    void on_pushButton_clicked();
    void on_pushButtonStartLabelling_clicked();
    void onNewInstruction(QString longStr, QString shortStr, bool back);
    void onImgNoChange(int, QString);
    void onBRectDone();

    void on_pushButtonYes_clicked();

    void on_pushButtonNo_clicked();

private:
    Ui::window_main *ui;
    XmlImageLoader* xmlImageLoader;
    XmlImageSaver* xmlImageSaver;
    ImageLabelingScene *scene;
};

#endif // WINDOW_MAIN_H
