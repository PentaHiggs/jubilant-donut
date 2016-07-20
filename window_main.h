#ifndef WINDOW_MAIN_H
#define WINDOW_MAIN_H

#include <QMainWindow>

namespace Ui {
class window_main;
}

class window_main : public QMainWindow
{
    Q_OBJECT

public:
    explicit window_main(QWidget *parent = 0);
    ~window_main();

private:
    Ui::window_main *ui;
};

#endif // WINDOW_MAIN_H
