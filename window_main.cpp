#include "window_main.h"
#include "ui_window_main.h"
#include "labeledimage.h"
#include "imagelabellingscene.h"

#include <QFileDialog>
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
    xmlImageLoader = new XmlImageLoader(xmlFile, QUrl::fromLocalFile(filename));

    ui->pushButtonStartLabelling->setEnabled(true);
}

void window_main::on_pushButtonStartLabelling_clicked()
{
    // We should load stuff!
    std::shared_ptr<LabeledImage> labeledImage = xmlImageLoader.next();
    if(labeledImage != nullptr) {
        // loading succeeded.  First lets create a scene, and place image in scene.
        ImageLabellingScene scene;
        ui->graphicsView->setScene(&scene);
        ui->graphicsView->fitInView(*labeledImage, Qt::KeepAspectRatio);

        // Now we need to hook up the ImageLabellingScene's slots to the LabeledImage signals
        QObject::connect(image, SIGNAL(mouseEnterImage(QPointF)), scene, SLOT(mouseEnterImage(QPointF)));
        QObject::connect(image, SIGNAL(mouseMoveOnImage(QPointF)), scene, SLOT(mouseMoveOnImage(QPointF)));
        QObject::connect(image, SIGNAL(mouseLeaveImage()), scene, SLOT(mouseLeaveImage()));
        QObject::connect(image, SIGNAL(mouseClickImage(QPointF)), scene, SLOT(mouseClickImage()));

        // Hook up the navigation buttons as well
        QObject::connect(ui->pushButtonNextStep, SIGNAL(clicked(bool)), scene, SLOT(forward()));
        QObject::connect(ui->pushButtonPreviousStep, SIGNAL(clicked(bool)), scene, SLOT(back()));


    } else {
        // loading failed, spawn popup telling user.
    }

}
