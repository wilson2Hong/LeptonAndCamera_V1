/********************************************************************************
** Form generated from reading UI file 'leptonandcamera.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LEPTONANDCAMERA_H
#define UI_LEPTONANDCAMERA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LeptonAndCamera
{
public:
    QWidget *centralWidget;
    QGraphicsView *leptonview;
    QGraphicsView *Cameraview;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pic;
    QPushButton *closeCam;
    QPushButton *open;
    QLabel *leptonView;
    QLabel *CameraView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *LeptonAndCamera)
    {
        if (LeptonAndCamera->objectName().isEmpty())
            LeptonAndCamera->setObjectName(QString::fromUtf8("LeptonAndCamera"));
        LeptonAndCamera->resize(710, 404);
        centralWidget = new QWidget(LeptonAndCamera);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        leptonview = new QGraphicsView(centralWidget);
        leptonview->setObjectName(QString::fromUtf8("leptonview"));
        leptonview->setGeometry(QRect(20, 20, 311, 291));
        Cameraview = new QGraphicsView(centralWidget);
        Cameraview->setObjectName(QString::fromUtf8("Cameraview"));
        Cameraview->setGeometry(QRect(340, 20, 351, 291));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(190, 0, 48, 15));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(480, 0, 48, 15));
        pic = new QPushButton(centralWidget);
        pic->setObjectName(QString::fromUtf8("pic"));
        pic->setGeometry(QRect(280, 320, 85, 25));
        closeCam = new QPushButton(centralWidget);
        closeCam->setObjectName(QString::fromUtf8("closeCam"));
        closeCam->setGeometry(QRect(500, 320, 85, 25));
        open = new QPushButton(centralWidget);
        open->setObjectName(QString::fromUtf8("open"));
        open->setGeometry(QRect(110, 320, 85, 25));
        leptonView = new QLabel(centralWidget);
        leptonView->setObjectName(QString::fromUtf8("leptonView"));
        leptonView->setGeometry(QRect(20, 20, 311, 291));
        CameraView = new QLabel(centralWidget);
        CameraView->setObjectName(QString::fromUtf8("CameraView"));
        CameraView->setGeometry(QRect(340, 20, 351, 291));
        LeptonAndCamera->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(LeptonAndCamera);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 710, 21));
        LeptonAndCamera->setMenuBar(menuBar);
        mainToolBar = new QToolBar(LeptonAndCamera);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        LeptonAndCamera->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(LeptonAndCamera);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        LeptonAndCamera->setStatusBar(statusBar);

        retranslateUi(LeptonAndCamera);

        QMetaObject::connectSlotsByName(LeptonAndCamera);
    } // setupUi

    void retranslateUi(QMainWindow *LeptonAndCamera)
    {
        LeptonAndCamera->setWindowTitle(QApplication::translate("LeptonAndCamera", "LeptonAndCamera", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("LeptonAndCamera", "Lepton", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("LeptonAndCamera", "Camera", 0, QApplication::UnicodeUTF8));
        pic->setText(QApplication::translate("LeptonAndCamera", "video", 0, QApplication::UnicodeUTF8));
        closeCam->setText(QApplication::translate("LeptonAndCamera", "CloseCam", 0, QApplication::UnicodeUTF8));
        open->setText(QApplication::translate("LeptonAndCamera", "OpenCamera", 0, QApplication::UnicodeUTF8));
        leptonView->setText(QString());
        CameraView->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LeptonAndCamera: public Ui_LeptonAndCamera {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LEPTONANDCAMERA_H
