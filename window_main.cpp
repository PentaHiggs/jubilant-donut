#include "window_main.h"
#include "ui_window_main.h"
#include "labeledimage.h"
#include "imagelabelingscene.h"

#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include <QMessageBox>

void setReadOnly(QTextEdit*);


window_main::window_main(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::window_main)
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
    // We can create our scene to stick in the graphics view
    ImageLabelingScene *scene = new ImageLabelingScene();
    ui->graphicsView->setScene(scene);

    // Lets take this opportunity to hook up our scene to the main_window
    QObject::connect(scene, SIGNAL(newInstruction(QString,QString,bool)),
                     this, SLOT(onNewInstruction(QString,QString,bool)));
    QObject::connect(ui->pushButtonNextStep, SIGNAL(clicked(bool)), scene, SLOT(forward()));
    QObject::connect(ui->pushButtonPreviousStep, SIGNAL(clicked(bool)), scene, SLOT(back()));


    LabeledImage *labeledImage;

    while ( (labeledImage = xmlImageLoader->next()) != nullptr)
    {
        // Stick image in scene
        // Now we need to hook up the ImageLabellingScene's slots to the LabeledImage signals
        QObject::connect(dynamic_cast<QObject*>(labeledImage), SIGNAL(mouseEnterImage(QPointF)),
                         dynamic_cast<QObject*>(scene), SLOT(mouseEnterImage(QPointF)));
        QObject::connect(dynamic_cast<QObject*>(labeledImage), SIGNAL(mouseMoveOnImage(QPointF)),
                         dynamic_cast<QObject*>(scene), SLOT(mouseMoveOnImage(QPointF)));
        QObject::connect(dynamic_cast<QObject*>(labeledImage), SIGNAL(mouseLeaveImage()),
                         dynamic_cast<QObject*>(scene), SLOT(mouseLeaveImage()));
        QObject::connect(dynamic_cast<QObject*>(labeledImage), SIGNAL(mouseClickImage(QPointF)),
                         dynamic_cast<QObject*>(scene), SLOT(mouseClickImage()));
    }

}

void window_main::onImgNoChange(int n, QString s) {
    ui->textBoxImageNumber->setText(QString("%1").arg(n));
    ui->textBoxImageLabel->setText(s);
}

void setReadOnly(QTextEdit* w) {
    w->setReadOnly(true);
    w->setTextInteractionFlags(
                Qt::TextSelectableByMouse | Qt::TextSelectableByKeyboard);
}
