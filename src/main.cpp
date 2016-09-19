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
    w.show();
    return a.exec();
}
