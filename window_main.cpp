#include "window_main.h"
#include "ui_window_main.h"
#include "labeledimage.h"

#include <QFileDialog>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>

window_main::window_main(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::window_main)
{
    ui->setupUi(this);

    // Set fielNameDisplayTextEdit to be read only but still selectable
    ui->fileNameDisplayTextEdit->setReadOnly(true);
    ui->fileNameDisplayTextEdit->setTextInteractionFlags(
                ui->fileNameDisplayTextEdit->textInteractionFlags() | Qt::TextSelectableByKeyboard);

    // Set widget stack to page_startPage and disable start button
    ui->stackedWidget->setCurrentIndex();
    ui->pushButtonStartLabelling->setEnabled(false);
}

window_main::~window_main()
{
    delete ui;
}

void window_main::on_pushButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Select XML File"),
                "C://",
                "XML files (*.xml);;Text files (*.txt);;All files (*.*)"
                );
    ui->fileNameDisplayTextEdit->setText(filename);
    QFile xmlFile = QFile(filename);
    if (!file.open(QIODevice::ReadWrite)){
        // Insert implementation of error dialog here
        return;
    }

    // Pass file to XML reader so it can get down to business
    xmlImageLoader = new XmlImageLoader(xmlFile);

    ui->pushButtonStartLabelling->setEnabled(true);
}

void window_main::on_pushButtonStartLabelling_clicked()
{
    // We should load stuff!
    std::shared_ptr<LabeledImage> labeledImage = xmlImageLoader.next();
    if(labeledImage != nullptr) {
        // loading succeeded.  First lets create a scene, and place image in scene.
        QGraphicsScene scene;;
        ui->graphicsView->fitInView(*labeledImage, Qt::KeepAspectRatio);


    } else {
        // loading failed, spawn popup telling user.
    }

}
