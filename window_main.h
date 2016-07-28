#ifndef WINDOW_MAIN_H
#define WINDOW_MAIN_H

#include <QMainWindow>

#include "xmlimageloader.h"

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

private:
    Ui::window_main *ui;
    std::shared_ptr<XmlImageLoader> xmlImageLoader;
    void setUpGraphics(LabeledImage* img);

};

#endif // WINDOW_MAIN_H
