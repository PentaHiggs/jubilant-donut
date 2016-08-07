#include "window_main.h"
#include "ui_window_main.h"
#include "labeledimage.h"
#include "imagelabelingscene.h"

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
    ui->stackedWidget->setCurrentIndex(0);
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
    QFile *xmlFile = new QFile(filename);
    if (!xmlFile->open(QIODevice::ReadWrite)){
        // Insert implementation of error dialog here
        return;
    }

    // Pass file to XML reader so it can get down to business
    xmlImageLoader = new XmlImageLoader(xmlFile, QUrl::fromLocalFile(filename));
    QObject::connect(xmlImageLoader, SIGNAL(setImgNo(int,QString)),
                     this, SLOT(onImgNoChange(int,QString)));
    ui->pushButtonStartLabelling->setEnabled(true);
}

void window_main::onNewInstruction(QString longStr, QString shortStr, bool back) {
    ui->textBrowserInstruction->setText(longStr);
    if (!shortStr.isEmpty())
    {
        if (!back) {
            ui->textBrowserInstructionsCompleted->insertPlainText(shortStr);
            ui->textBrowserInstructionsCompleted->insertPlainText("\n");
        } else {
            // how to delete a line...
            QString txt = ui->textBrowserInstructionsCompleted->toPlainText()
                    .section("/n", 0, -2, QString::SectionIncludeTrailingSep);
            txt.append("shortStr");

            ui->textBrowserInstructionsCompleted->setText(txt);
        }
    }
}

void window_main::on_pushButtonStartLabelling_clicked()
{
    // We should load stuff!
    LabeledImage *labeledImage = xmlImageLoader->next();
    if(labeledImage != nullptr) {
        // loading succeeded.  First lets create a scene, and place image in scene.
        ImageLabelingScene *scene = new ImageLabelingScene(*labeledImage);
        ui->graphicsView->setScene(scene);
        // ui->graphicsView->fitInView(*labeledImage, Qt::KeepAspectRatio);

        // Now we need to hook up the ImageLabellingScene's slots to the LabeledImage signals
        QObject::connect(dynamic_cast<QObject*>(labeledImage), SIGNAL(mouseEnterImage(QPointF)),
                         dynamic_cast<QObject*>(scene), SLOT(mouseEnterImage(QPointF)));
        QObject::connect(dynamic_cast<QObject*>(labeledImage), SIGNAL(mouseMoveOnImage(QPointF)),
                         dynamic_cast<QObject*>(scene), SLOT(mouseMoveOnImage(QPointF)));
        QObject::connect(dynamic_cast<QObject*>(labeledImage), SIGNAL(mouseLeaveImage()),
                         dynamic_cast<QObject*>(scene), SLOT(mouseLeaveImage()));
        QObject::connect(dynamic_cast<QObject*>(labeledImage), SIGNAL(mouseClickImage(QPointF)),
                         dynamic_cast<QObject*>(scene), SLOT(mouseClickImage()));
        QObject::connect(scene, SIGNAL(newInstruction(QString,QString,bool)),
                         this, SLOT(onNewInstruction(QString,QString,bool)));


        // Hook up the navigation buttons as well
        QObject::connect(ui->pushButtonNextStep, SIGNAL(clicked(bool)), scene, SLOT(forward()));
        QObject::connect(ui->pushButtonPreviousStep, SIGNAL(clicked(bool)), scene, SLOT(back()));


    } else {
        // loading failed, spawn popup telling user.
    }

}

void window_main::onImgNoChange(int n, QString s) {
    ui->textBoxImageNumber->setText(QString("%1").arg(n));
    ui->textBoxImageLabel->setText(s);
}
