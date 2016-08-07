#include "window_main.h"
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QVBoxLayout>
#include <QLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    window_main w;
    /*
     * // Beneath is code from previous testing
    QGraphicsScene scene;
    QGraphicsView view(&scene);

    QImage img;
    img.load("E:/leaf.jpg");

    QGraphicsPixmapItem item( QPixmap::fromImage(img));
    scene.addItem(&item);

    w.layout()->addWidget(&view); */
    w.show();
    return a.exec();
}
