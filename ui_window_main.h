/********************************************************************************
** Form generated from reading UI file 'window_main.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_MAIN_H
#define UI_WINDOW_MAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_window_main
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QGraphicsView *graphicsView;
    QGroupBox *groupBox_xmlFile;
    QTextEdit *fileNameDisplayTextEdit;
    QPushButton *pushButton;
    QPushButton *loadImagesXmlPushButton;
    QGroupBox *groupBox_interImageNavigation;
    QPushButton *pushButtonLast;
    QPushButton *pushButtonNext;
    QTextBrowser *textBoxImageNumber;
    QTextBrowser *textBoxImageLabel;
    QPushButton *pushButtonSave;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButtonJumpToImage;
    QGroupBox *groupBox_intraImageNavigation;
    QStackedWidget *stackedWidget;
    QWidget *page_startPage;
    QPushButton *pushButtonStartLabelling;
    QWidget *page_instructionsPage;
    QPushButton *pushButtonPreviousStep;
    QPushButton *pushButtonNextStep;
    QLabel *label;
    QTextBrowser *textBrowserInstruction;
    QLabel *label_4;
    QTextBrowser *textBrowserInstructionsCompleted;
    QWidget *page_yesNoPrompt;
    QLabel *label_5;
    QPushButton *pushButtonYes;
    QPushButton *pushButtonNo;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *window_main)
    {
        if (window_main->objectName().isEmpty())
            window_main->setObjectName(QStringLiteral("window_main"));
        window_main->resize(1066, 609);
        centralWidget = new QWidget(window_main);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 721, 551));
        graphicsView = new QGraphicsView(groupBox);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(10, 20, 701, 521));
        groupBox_xmlFile = new QGroupBox(centralWidget);
        groupBox_xmlFile->setObjectName(QStringLiteral("groupBox_xmlFile"));
        groupBox_xmlFile->setGeometry(QRect(730, 0, 331, 91));
        fileNameDisplayTextEdit = new QTextEdit(groupBox_xmlFile);
        fileNameDisplayTextEdit->setObjectName(QStringLiteral("fileNameDisplayTextEdit"));
        fileNameDisplayTextEdit->setGeometry(QRect(0, 20, 261, 31));
        fileNameDisplayTextEdit->setMaximumSize(QSize(16777215, 71));
        pushButton = new QPushButton(groupBox_xmlFile);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(270, 20, 61, 31));
        loadImagesXmlPushButton = new QPushButton(groupBox_xmlFile);
        loadImagesXmlPushButton->setObjectName(QStringLiteral("loadImagesXmlPushButton"));
        loadImagesXmlPushButton->setGeometry(QRect(0, 60, 329, 23));
        groupBox_interImageNavigation = new QGroupBox(centralWidget);
        groupBox_interImageNavigation->setObjectName(QStringLiteral("groupBox_interImageNavigation"));
        groupBox_interImageNavigation->setGeometry(QRect(730, 90, 331, 181));
        pushButtonLast = new QPushButton(groupBox_interImageNavigation);
        pushButtonLast->setObjectName(QStringLiteral("pushButtonLast"));
        pushButtonLast->setGeometry(QRect(10, 30, 75, 23));
        pushButtonNext = new QPushButton(groupBox_interImageNavigation);
        pushButtonNext->setObjectName(QStringLiteral("pushButtonNext"));
        pushButtonNext->setGeometry(QRect(250, 30, 75, 23));
        textBoxImageNumber = new QTextBrowser(groupBox_interImageNavigation);
        textBoxImageNumber->setObjectName(QStringLiteral("textBoxImageNumber"));
        textBoxImageNumber->setGeometry(QRect(80, 60, 241, 31));
        textBoxImageLabel = new QTextBrowser(groupBox_interImageNavigation);
        textBoxImageLabel->setObjectName(QStringLiteral("textBoxImageLabel"));
        textBoxImageLabel->setGeometry(QRect(80, 100, 241, 31));
        pushButtonSave = new QPushButton(groupBox_interImageNavigation);
        pushButtonSave->setObjectName(QStringLiteral("pushButtonSave"));
        pushButtonSave->setGeometry(QRect(130, 30, 75, 23));
        label_2 = new QLabel(groupBox_interImageNavigation);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 70, 31, 16));
        label_3 = new QLabel(groupBox_interImageNavigation);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 110, 47, 13));
        pushButtonJumpToImage = new QPushButton(groupBox_interImageNavigation);
        pushButtonJumpToImage->setObjectName(QStringLiteral("pushButtonJumpToImage"));
        pushButtonJumpToImage->setGeometry(QRect(64, 140, 201, 23));
        groupBox_intraImageNavigation = new QGroupBox(centralWidget);
        groupBox_intraImageNavigation->setObjectName(QStringLiteral("groupBox_intraImageNavigation"));
        groupBox_intraImageNavigation->setGeometry(QRect(730, 270, 331, 281));
        stackedWidget = new QStackedWidget(groupBox_intraImageNavigation);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 20, 331, 251));
        page_startPage = new QWidget();
        page_startPage->setObjectName(QStringLiteral("page_startPage"));
        pushButtonStartLabelling = new QPushButton(page_startPage);
        pushButtonStartLabelling->setObjectName(QStringLiteral("pushButtonStartLabelling"));
        pushButtonStartLabelling->setGeometry(QRect(60, 40, 211, 171));
        stackedWidget->addWidget(page_startPage);
        page_instructionsPage = new QWidget();
        page_instructionsPage->setObjectName(QStringLiteral("page_instructionsPage"));
        pushButtonPreviousStep = new QPushButton(page_instructionsPage);
        pushButtonPreviousStep->setObjectName(QStringLiteral("pushButtonPreviousStep"));
        pushButtonPreviousStep->setGeometry(QRect(0, 10, 121, 23));
        pushButtonNextStep = new QPushButton(page_instructionsPage);
        pushButtonNextStep->setObjectName(QStringLiteral("pushButtonNextStep"));
        pushButtonNextStep->setGeometry(QRect(210, 10, 121, 23));
        label = new QLabel(page_instructionsPage);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(120, 40, 91, 20));
        textBrowserInstruction = new QTextBrowser(page_instructionsPage);
        textBrowserInstruction->setObjectName(QStringLiteral("textBrowserInstruction"));
        textBrowserInstruction->setGeometry(QRect(10, 60, 311, 61));
        label_4 = new QLabel(page_instructionsPage);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(110, 130, 111, 20));
        textBrowserInstructionsCompleted = new QTextBrowser(page_instructionsPage);
        textBrowserInstructionsCompleted->setObjectName(QStringLiteral("textBrowserInstructionsCompleted"));
        textBrowserInstructionsCompleted->setGeometry(QRect(5, 150, 321, 101));
        stackedWidget->addWidget(page_instructionsPage);
        page_yesNoPrompt = new QWidget();
        page_yesNoPrompt->setObjectName(QStringLiteral("page_yesNoPrompt"));
        label_5 = new QLabel(page_yesNoPrompt);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 20, 281, 41));
        pushButtonYes = new QPushButton(page_yesNoPrompt);
        pushButtonYes->setObjectName(QStringLiteral("pushButtonYes"));
        pushButtonYes->setGeometry(QRect(100, 60, 131, 81));
        pushButtonNo = new QPushButton(page_yesNoPrompt);
        pushButtonNo->setObjectName(QStringLiteral("pushButtonNo"));
        pushButtonNo->setGeometry(QRect(100, 150, 131, 81));
        stackedWidget->addWidget(page_yesNoPrompt);
        window_main->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(window_main);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1066, 21));
        window_main->setMenuBar(menuBar);
        mainToolBar = new QToolBar(window_main);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        window_main->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(window_main);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        window_main->setStatusBar(statusBar);

        retranslateUi(window_main);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(window_main);
    } // setupUi

    void retranslateUi(QMainWindow *window_main)
    {
        window_main->setWindowTitle(QApplication::translate("window_main", "window_main", 0));
        groupBox->setTitle(QApplication::translate("window_main", "Image", 0));
        groupBox_xmlFile->setTitle(QApplication::translate("window_main", "XML File", 0));
        pushButton->setText(QApplication::translate("window_main", "Open File", 0));
        loadImagesXmlPushButton->setText(QApplication::translate("window_main", "Load Images XML", 0));
        groupBox_interImageNavigation->setTitle(QApplication::translate("window_main", "Inter-image Navigation", 0));
        pushButtonLast->setText(QApplication::translate("window_main", "< Last", 0));
        pushButtonNext->setText(QApplication::translate("window_main", " Next >", 0));
        pushButtonSave->setText(QApplication::translate("window_main", "Save", 0));
        label_2->setText(QApplication::translate("window_main", "Img #", 0));
        label_3->setText(QApplication::translate("window_main", "Img Label", 0));
        pushButtonJumpToImage->setText(QApplication::translate("window_main", "Jump to Image...", 0));
        groupBox_intraImageNavigation->setTitle(QApplication::translate("window_main", "Intra-image Navigation", 0));
        pushButtonStartLabelling->setText(QApplication::translate("window_main", "Start Labelling", 0));
        pushButtonPreviousStep->setText(QApplication::translate("window_main", " < Previous Step ", 0));
        pushButtonNextStep->setText(QApplication::translate("window_main", "Next Step >", 0));
        label->setText(QApplication::translate("window_main", "Current Instruction", 0));
        label_4->setText(QApplication::translate("window_main", "Instructions Completed", 0));
        label_5->setText(QApplication::translate("window_main", "Are there any more bounding boxes to label in this image?", 0));
        pushButtonYes->setText(QApplication::translate("window_main", "Yes", 0));
        pushButtonNo->setText(QApplication::translate("window_main", "No", 0));
    } // retranslateUi

};

namespace Ui {
    class window_main: public Ui_window_main {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_MAIN_H
