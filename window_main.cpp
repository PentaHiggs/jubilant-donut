#include "window_main.h"
#include "ui_window_main.h"

window_main::window_main(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::window_main)
{
    ui->setupUi(this);
}

window_main::~window_main()
{
    delete ui;
}
