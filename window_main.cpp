#include "window_main.h"
#include "ui_window_main.h"
#include "labeledimage.h"
#include "imagelabelingscene.h"

#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QMessageBox>

void setReadOnly(QTextEdit*);
void hookUpImage(LabeledImage*, ImageLabelingScene*);

window_main::window_main(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::window_main),
    scene(nullptr)
{
    ui->setupUi(this);

    // Set the display text boxes to be read-only but still selectable.
    setReadOnly(ui->fileNameDisplayTextEdit);
    setReadOnly(ui->textBoxImageLabel);
    setReadOnly(ui->textBoxImageNumber);
    setReadOnly(ui->textBrowserInstruction);
    setReadOnly(ui->textBrowserInstructionsCompleted);

    // Set widget stack to page_startPage and disable start button
    ui->stackedWidget->setCurrentIndex(0);
    ui->pushButtonStartLabelling->setEnabled(false);
}

window_main::~window_main()
{
    delete ui;
    delete scene;
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
        QMessageBox msgBox;
        msgBox.setText("Cannot open file with read/write permissions.  Make certain this program has\
                       complete permissions to edit this file");
        msgBox.exec();
        return;
    }

    // Pass file to XML reader so it can get down to business
    xmlImageLoader = new XmlImageLoader(xmlFile, QUrl::fromLocalFile(filename));
    QObject::connect(xmlImageLoader, SIGNAL(setImgNo(int,QString)),
                     this, SLOT(onImgNoChange(int,QString)));
    // We can now push the button to get down to business!
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
    // Start and set up XML writer

    // Change stackedWidget page to the right one for labeling
    ui->stackedWidget->setCurrentIndex(1);

    if (scene == nullptr) {
        scene = new ImageLabelingScene();
        ui->graphicsView->setScene(scene);

        // Lets take this opportunity to hook up our scene to the main_window
        QObject::connect(scene, SIGNAL(newInstruction(QString,QString,bool)),
                         this, SLOT(onNewInstruction(QString,QString,bool)));
        QObject::connect(scene, SIGNAL(bRectDone()), this, SLOT(onBRectDone()));
        QObject::connect(ui->pushButtonNextStep, SIGNAL(clicked(bool)), scene, SLOT(forward()));
        QObject::connect(ui->pushButtonPreviousStep, SIGNAL(clicked(bool)), scene, SLOT(back()));
    }
    LabeledImage *labeledImage;

    if  ( (labeledImage = xmlImageLoader->next()) != nullptr)
    {
        // Stick image in scene
        void hookUpImage(LabeledImage* labeledImage, ImageLabelingScene* scene);
    } else {
        //
    }

}

void window_main::onImgNoChange(int n, QString s) {
    ui->textBoxImageNumber->setText(QString("%1").arg(n));
    ui->textBoxImageLabel->setText(s);
}

void window_main::onBRectDone(){
    ui->stackedWidget->setCurrentIndex(2);
}

void setReadOnly(QTextEdit* w) {
    w->setReadOnly(true);
    w->setTextInteractionFlags(
                Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
}

void window_main::on_pushButtonYes_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void window_main::on_pushButtonNo_clicked()
{
    // Insert some code for adding the image to the XML file
    LabeledImage* labeledImage;
    // Load the next image
    if  ( (labeledImage = xmlImageLoader->next()) != nullptr)
        hookUpImage(labeledImage, this->scene);
    else {
        // We're outta stuff!  Let XML know
    }

}

void hookUpImage(LabeledImage* labeledImage, ImageLabelingScene* scene){
    QObject::connect(dynamic_cast<QObject*>(labeledImage), SIGNAL(mouseEnterImage(QPointF)),
                     dynamic_cast<QObject*>(scene), SLOT(mouseEnterImage(QPointF)));
    QObject::connect(dynamic_cast<QObject*>(labeledImage), SIGNAL(mouseMoveOnImage(QPointF)),
                     dynamic_cast<QObject*>(scene), SLOT(mouseMoveOnImage(QPointF)));
    QObject::connect(dynamic_cast<QObject*>(labeledImage), SIGNAL(mouseLeaveImage()),
                     dynamic_cast<QObject*>(scene), SLOT(mouseLeaveImage()));
    QObject::connect(dynamic_cast<QObject*>(labeledImage), SIGNAL(mouseClickImage(QPointF)),
                     dynamic_cast<QObject*>(scene), SLOT(mouseClickImage()));
    scene->changeImage(*labeledImage);
}
